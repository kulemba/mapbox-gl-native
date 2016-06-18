#pragma once

#include <mbgl/style/sources/geojson_source.hpp>
#include <mbgl/style/source_impl.hpp>
#include <mbgl/util/rapidjson.hpp>
#include <mbgl/util/variant.hpp>

namespace mapbox {
namespace geojsonvt {
class GeoJSONVT;
} // namespace geojsonvt
} // namespace mapbox

namespace mbgl {

class AsyncRequest;

namespace style {

class GeoJSONSource::Impl : public Source::Impl {
public:
    using GeoJSON = std::unique_ptr<mapbox::geojsonvt::GeoJSONVT>;

    static std::unique_ptr<GeoJSONSource> parse(const std::string& id, const JSValue&);
    static GeoJSON parseGeoJSON(const JSValue&);

    Impl(std::string id, Source&,
         variant<std::string, GeoJSON> urlOrGeoJSON);
    ~Impl() final;

    void load(FileSource&) final;

    uint16_t getTileSize() const final {
        return util::tileSize;
    }

    const variant<std::string, GeoJSON>& getURLOrGeoJSON() const {
        return urlOrGeoJSON;
    }

private:
    Range<uint8_t> getZoomRange() final;
    std::unique_ptr<Tile> createTile(const OverscaledTileID&, const UpdateParameters&) final;

    variant<std::string, GeoJSON> urlOrGeoJSON;
    std::unique_ptr<AsyncRequest> req;
};

} // namespace style
} // namespace mbgl
