#include <mbgl/style/sources/geojson_source_impl.hpp>
#include <mbgl/style/source_observer.hpp>
#include <mbgl/style/parser.hpp>
#include <mbgl/tile/geojson_tile.hpp>
#include <mbgl/storage/file_source.hpp>
#include <mbgl/platform/log.hpp>

#include <mapbox/geojsonvt.hpp>
#include <mapbox/geojsonvt/convert.hpp>

#include <rapidjson/error/en.h>

#include <sstream>

namespace mbgl {
namespace style {

std::unique_ptr<mapbox::geojsonvt::GeoJSONVT> GeoJSONSource::Impl::parseGeoJSON(const JSValue& value) {
    using namespace mapbox::geojsonvt;

    Options options;
    options.buffer = util::EXTENT / util::tileSize * 128;
    options.extent = util::EXTENT;

    try {
        return std::make_unique<GeoJSONVT>(Convert::convert(value, 0), options);
    } catch (const std::exception& ex) {
        Log::Error(Event::ParseStyle, "Failed to parse GeoJSON data: %s", ex.what());
        // Create an empty GeoJSON VT object to make sure we're not infinitely waiting for
        // tiles to load.
        return std::make_unique<GeoJSONVT>(std::vector<ProjectedFeature>{}, options);
    }
}

std::unique_ptr<GeoJSONSource> GeoJSONSource::Impl::parse(const std::string& id, const JSValue& value) {
    // We should probably split this up to have URLs in the url property, and actual data
    // in the data property. Until then, we're going to detect the content based on the
    // object type.
    if (!value.HasMember("data")) {
        Log::Error(Event::ParseStyle, "GeoJSON source must have a data value");
        return nullptr;
    }

    const JSValue& dataVal = value["data"];
    if (dataVal.IsString()) {
        return std::make_unique<GeoJSONSource>([&] (Source& base) {
            return std::make_unique<Impl>(id, base, std::string(dataVal.GetString(), dataVal.GetStringLength()));
        });
    } else if (dataVal.IsObject()) {
        return std::make_unique<GeoJSONSource>([&] (Source& base) {
            return std::make_unique<Impl>(id, base, parseGeoJSON(dataVal));
        });
    } else {
        Log::Error(Event::ParseStyle, "GeoJSON data must be a URL or an object");
        return nullptr;
    }
}

GeoJSONSource::Impl::Impl(std::string id_, Source& base_, variant<std::string, GeoJSON> urlOrGeoJSON_)
    : Source::Impl(SourceType::GeoJSON, std::move(id_), base_),
      urlOrGeoJSON(std::move(urlOrGeoJSON_)) {
}

GeoJSONSource::Impl::~Impl() = default;

void GeoJSONSource::Impl::load(FileSource& fileSource) {
    if (urlOrGeoJSON.is<GeoJSON>()) {
        loaded = true;
        return;
    }

    if (req) {
        return;
    }

    const std::string& url = urlOrGeoJSON.get<std::string>();
    req = fileSource.request(Resource::source(url), [this](Response res) {
        if (res.error) {
            observer->onSourceError(base, std::make_exception_ptr(std::runtime_error(res.error->message)));
        } else if (res.notModified) {
            return;
        } else if (res.noContent) {
            observer->onSourceError(base, std::make_exception_ptr(std::runtime_error("unexpectedly empty GeoJSON")));
        } else {
            rapidjson::GenericDocument<rapidjson::UTF8<>, rapidjson::CrtAllocator> d;
            d.Parse<0>(res.data->c_str());

            if (d.HasParseError()) {
                std::stringstream message;
                message << d.GetErrorOffset() << " - " << rapidjson::GetParseError_En(d.GetParseError());
                observer->onSourceError(base, std::make_exception_ptr(std::runtime_error(message.str())));
                return;
            }

            invalidateTiles();

            urlOrGeoJSON = parseGeoJSON(d);
            loaded = true;

            observer->onSourceLoaded(base);
        }
    });
}

Range<uint8_t> GeoJSONSource::Impl::getZoomRange() {
    assert(loaded);
    return { 0, urlOrGeoJSON.get<GeoJSON>()->options.maxZoom };
}

std::unique_ptr<Tile> GeoJSONSource::Impl::createTile(const OverscaledTileID& tileID,
                                                const UpdateParameters& parameters) {
    assert(loaded);
    return std::make_unique<GeoJSONTile>(tileID, base.getID(), parameters, *urlOrGeoJSON.get<GeoJSON>());
}

} // namespace style
} // namespace mbgl
