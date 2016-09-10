#include <mbgl/storage/default_file_source.hpp>
#include <mbgl/storage/asset_file_source.hpp>
#include <mbgl/storage/online_file_source.hpp>
#include <mbgl/storage/offline_database.hpp>
#include <mbgl/storage/offline_download.hpp>

#include <mbgl/platform/platform.hpp>
#include <mbgl/util/url.hpp>
#include <mbgl/util/thread.hpp>
#include <mbgl/util/work_request.hpp>
#include <mbgl/tile/tile_id.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/box.hpp>
#pragma GCC diagnostic pop

#include <cassert>

namespace {

const std::string assetProtocol = "asset://";

bool isAssetURL(const std::string& url) {
    return std::equal(assetProtocol.begin(), assetProtocol.end(), url.begin());
}

} // namespace

BOOST_GEOMETRY_REGISTER_POINT_2D(mbgl::LatLng, double, boost::geometry::cs::cartesian, longitude, latitude)
BOOST_GEOMETRY_REGISTER_BOX(mbgl::LatLngBounds, mbgl::LatLng, southwest(), northeast())

namespace mbgl {

class DefaultFileSource::Impl {
public:
    Impl(const std::string& cachePath, uint64_t maximumCacheSize)
        : offlineDatabase(cachePath, maximumCacheSize) {
    }

    void setAccessToken(const std::string& accessToken) {
        onlineFileSource.setAccessToken(accessToken);
    }

    std::string getAccessToken() const {
        return onlineFileSource.getAccessToken();
    }

    void listRegions(std::function<void (std::exception_ptr, optional<std::vector<OfflineRegion>>)> callback) {
        try {
            callback({}, offlineDatabase.listRegions());
        } catch (...) {
            callback(std::current_exception(), {});
        }
    }

    void createRegion(const OfflineRegionDefinition& definition,
                      const OfflineRegionMetadata& metadata,
                      std::function<void (std::exception_ptr, optional<OfflineRegion>)> callback) {
        try {
            callback({}, offlineDatabase.createRegion(definition, metadata));
        } catch (...) {
            callback(std::current_exception(), {});
        }
    }

    void getRegionStatus(int64_t regionID, std::function<void (std::exception_ptr, optional<OfflineRegionStatus>)> callback) {
        try {
            callback({}, getDownload(regionID).getStatus());
        } catch (...) {
            callback(std::current_exception(), {});
        }
    }

    void deleteRegion(OfflineRegion&& region, std::function<void (std::exception_ptr)> callback) {
        try {
            downloads.erase(region.getID());
            offlineDatabase.deleteRegion(std::move(region));
            callback({});
        } catch (...) {
            callback(std::current_exception());
        }
    }

    void setRegionObserver(int64_t regionID, std::unique_ptr<OfflineRegionObserver> observer) {
        getDownload(regionID).setObserver(std::move(observer));
    }

    void setRegionDownloadState(int64_t regionID, OfflineRegionDownloadState state) {
        getDownload(regionID).setState(state);
    }

    void request(AsyncRequest* req, Resource resource, Callback callback) {
        Resource revalidation = resource;

        const bool hasPrior = resource.priorEtag || resource.priorModified || resource.priorExpires;
        if (!hasPrior || resource.necessity == Resource::Optional) {
            auto offlineResponse = offlineDatabase.get(resource);

            if (! offlineResponse) {
                auto supplementaryCachePathsOfKind = supplementaryCachePaths.find(resource.kind);
                if (supplementaryCachePathsOfKind != supplementaryCachePaths.end()) {
                    const auto &latLngBoundsCachePathTree = supplementaryCachePathsOfKind->second;
                    auto qCachePathsBegin = resource.tileData ? latLngBoundsCachePathTree.qbegin(boost::geometry::index::intersects(LatLngBounds(CanonicalTileID(resource.tileData->z, resource.tileData->x, resource.tileData->y)))): latLngBoundsCachePathTree.qbegin(boost::geometry::index::contains(LatLng()));
                    auto qCachePathsEnd = latLngBoundsCachePathTree.qend();
                    for (auto j = qCachePathsBegin; ! offlineResponse && j != qCachePathsEnd; ++ j) {
                        const auto &cachePath = j->second;
                        auto supplementaryOfflineDatabase = supplementaryOfflineDatabases.find(cachePath);
                        if (supplementaryOfflineDatabase == supplementaryOfflineDatabases.end()) {
                            supplementaryOfflineDatabase = supplementaryOfflineDatabases.emplace(cachePath, std::make_unique<OfflineDatabase>(cachePath)).first;
                        }
                        if (supplementaryOfflineDatabase != supplementaryOfflineDatabases.end()) {
                            offlineResponse = supplementaryOfflineDatabase->second->get(resource);
                        }
                    }
                }
            }
            
            if (resource.necessity == Resource::Optional && !offlineResponse) {
                // Ensure there's always a response that we can send, so the caller knows that
                // there's no optional data available in the cache.
                offlineResponse.emplace();
                offlineResponse->noContent = true;
                offlineResponse->error = std::make_unique<Response::Error>(
                    Response::Error::Reason::NotFound, "Not found in offline database");
            }

            if (offlineResponse) {
                revalidation.priorModified = offlineResponse->modified;
                revalidation.priorExpires = offlineResponse->expires;
                revalidation.priorEtag = offlineResponse->etag;
                callback(*offlineResponse);
            }
        }

        if (resource.necessity == Resource::Required) {
            tasks[req] = onlineFileSource.request(revalidation, [=] (Response onlineResponse) {
                this->offlineDatabase.put(revalidation, onlineResponse);
                callback(onlineResponse);
            });
        }
    }

    void cancel(AsyncRequest* req) {
        tasks.erase(req);
    }

    void setOfflineMapboxTileCountLimit(uint64_t limit) {
        offlineDatabase.setOfflineMapboxTileCountLimit(limit);
    }

    void addSupplementaryOfflineDatabase(Resource::Kind kind, optional<LatLngBounds> latLngBounds, const std::string& cachePath) {
        auto supplementaryCachePathsOfKind = supplementaryCachePaths.find(kind);
        if (supplementaryCachePathsOfKind == supplementaryCachePaths.end())
            supplementaryCachePathsOfKind = supplementaryCachePaths.emplace(kind, LatLngBoundsCachePathTree()).first;
        if (supplementaryCachePathsOfKind != supplementaryCachePaths.end())
            supplementaryCachePathsOfKind->second.insert(LatLngBoundsCachePath(latLngBounds ? *latLngBounds: LatLngBounds::world(), cachePath));
    }
    
    void removeSupplementaryOfflineDatabases(const std::string& cachePath) {
        supplementaryOfflineDatabases.erase(cachePath);
        for (auto i = supplementaryCachePaths.begin(); i != supplementaryCachePaths.end(); ++ i) {
            auto &latLngBoundsCachePathTree = i->second;
            bool completed = false;
            while (! completed) {
                auto qCachePathsBegin = latLngBoundsCachePathTree.qbegin(boost::geometry::index::satisfies([cachePath] (const LatLngBoundsCachePath &latLngBoundsCachePath) {
                    return latLngBoundsCachePath.second == cachePath;
                }));
                auto qCachePathsEnd = latLngBoundsCachePathTree.qend();
                if (qCachePathsBegin == qCachePathsEnd)
                    completed = true;
                else
                    latLngBoundsCachePathTree.remove(*qCachePathsBegin);
            }
        }
    }
    
    void put(const Resource& resource, const Response& response) {
        offlineDatabase.put(resource, response);
    }

private:
    typedef std::pair<LatLngBounds, std::string> LatLngBoundsCachePath;
    typedef boost::geometry::index::rtree<LatLngBoundsCachePath, boost::geometry::index::rstar<16>> LatLngBoundsCachePathTree;
    typedef std::unordered_map<Resource::Kind, LatLngBoundsCachePathTree> ResourceKindLatLngBoundsCachePathTrees;

    OfflineDownload& getDownload(int64_t regionID) {
        auto it = downloads.find(regionID);
        if (it != downloads.end()) {
            return *it->second;
        }
        return *downloads.emplace(regionID,
            std::make_unique<OfflineDownload>(regionID, offlineDatabase.getRegionDefinition(regionID), offlineDatabase, onlineFileSource)).first->second;
    }

    OfflineDatabase offlineDatabase;
    OnlineFileSource onlineFileSource;
    std::unordered_map<AsyncRequest*, std::unique_ptr<AsyncRequest>> tasks;
    std::unordered_map<int64_t, std::unique_ptr<OfflineDownload>> downloads;
    
    std::unordered_map<std::string, std::unique_ptr<OfflineDatabase>> supplementaryOfflineDatabases;
    ResourceKindLatLngBoundsCachePathTrees supplementaryCachePaths;
};

DefaultFileSource::DefaultFileSource(const std::string& cachePath,
                                     const std::string& assetRoot,
                                     uint64_t maximumCacheSize)
    : thread(std::make_unique<util::Thread<Impl>>(util::ThreadContext{"DefaultFileSource", util::ThreadPriority::Low},
            cachePath, maximumCacheSize)),
      assetFileSource(std::make_unique<AssetFileSource>(assetRoot)) {
}

DefaultFileSource::~DefaultFileSource() = default;

void DefaultFileSource::setAccessToken(const std::string& accessToken) {
    thread->invokeSync(&Impl::setAccessToken, accessToken);
}

std::string DefaultFileSource::getAccessToken() const {
    return thread->invokeSync(&Impl::getAccessToken);
}

std::unique_ptr<AsyncRequest> DefaultFileSource::request(const Resource& resource, Callback callback) {
    class DefaultFileRequest : public AsyncRequest {
    public:
        DefaultFileRequest(Resource resource_, FileSource::Callback callback_, util::Thread<DefaultFileSource::Impl>& thread_)
            : thread(thread_),
              workRequest(thread.invokeWithCallback(&DefaultFileSource::Impl::request, this, resource_, callback_)) {
        }

        ~DefaultFileRequest() override {
            thread.invoke(&DefaultFileSource::Impl::cancel, this);
        }

        util::Thread<DefaultFileSource::Impl>& thread;
        std::unique_ptr<AsyncRequest> workRequest;
    };

    if (isAssetURL(resource.url)) {
        return assetFileSource->request(resource, callback);
    } else {
        return std::make_unique<DefaultFileRequest>(resource, callback, *thread);
    }
}

void DefaultFileSource::listOfflineRegions(std::function<void (std::exception_ptr, optional<std::vector<OfflineRegion>>)> callback) {
    thread->invoke(&Impl::listRegions, callback);
}

void DefaultFileSource::createOfflineRegion(const OfflineRegionDefinition& definition,
                                            const OfflineRegionMetadata& metadata,
                                            std::function<void (std::exception_ptr, optional<OfflineRegion>)> callback) {
    thread->invoke(&Impl::createRegion, definition, metadata, callback);
}

void DefaultFileSource::deleteOfflineRegion(OfflineRegion&& region, std::function<void (std::exception_ptr)> callback) {
    thread->invoke(&Impl::deleteRegion, std::move(region), callback);
}

void DefaultFileSource::setOfflineRegionObserver(OfflineRegion& region, std::unique_ptr<OfflineRegionObserver> observer) {
    thread->invoke(&Impl::setRegionObserver, region.getID(), std::move(observer));
}

void DefaultFileSource::setOfflineRegionDownloadState(OfflineRegion& region, OfflineRegionDownloadState state) {
    thread->invoke(&Impl::setRegionDownloadState, region.getID(), state);
}

void DefaultFileSource::getOfflineRegionStatus(OfflineRegion& region, std::function<void (std::exception_ptr, optional<OfflineRegionStatus>)> callback) const {
    thread->invoke(&Impl::getRegionStatus, region.getID(), callback);
}

void DefaultFileSource::setOfflineMapboxTileCountLimit(uint64_t limit) const {
    thread->invokeSync(&Impl::setOfflineMapboxTileCountLimit, limit);
}

void DefaultFileSource::addSupplementaryOfflineDatabase(Resource::Kind kind, optional<LatLngBounds> latLngBounds, const std::string& cachePath) {
    thread->invokeSync(&Impl::addSupplementaryOfflineDatabase, kind, latLngBounds, cachePath);
}

void DefaultFileSource::removeSupplementaryOfflineDatabases(const std::string& cachePath) {
    thread->invokeSync(&Impl::removeSupplementaryOfflineDatabases, cachePath);
}

// For testing only:

void DefaultFileSource::put(const Resource& resource, const Response& response) {
    thread->invokeSync(&Impl::put, resource, response);
}

} // namespace mbgl
