#include <mbgl/test/util.hpp>
#include <mbgl/test/stub_file_source.hpp>
#include <mbgl/test/fixture_log_observer.hpp>

#include <mbgl/style/style.hpp>
#include <mbgl/style/source_impl.hpp>
#include <mbgl/style/sources/vector_source.hpp>
#include <mbgl/style/layer.hpp>
#include <mbgl/style/layers/line_layer.hpp>
#include <mbgl/util/io.hpp>
#include <mbgl/util/run_loop.hpp>
#include <mbgl/util/default_thread_pool.hpp>

#include <memory>

using namespace mbgl;
using namespace mbgl::style;

TEST(Style, Properties) {
    util::RunLoop loop;

    ThreadPool threadPool{ 1 };
    StubFileSource fileSource;
    Style style { threadPool, fileSource, 1.0 };

    style.setJSON(R"STYLE({"name": "Test"})STYLE");
    ASSERT_EQ("Test", style.getName());

    style.setJSON(R"STYLE({"center": [10, 20]})STYLE");
    ASSERT_EQ("", style.getName());
    ASSERT_EQ((LatLng{20, 10}), style.getDefaultLatLng());

    style.setJSON(R"STYLE({"bearing": 24})STYLE");
    ASSERT_EQ("", style.getName());
    ASSERT_EQ((LatLng{0, 0}), style.getDefaultLatLng());
    ASSERT_EQ(24, style.getDefaultBearing());

    style.setJSON(R"STYLE({"zoom": 13.3})STYLE");
    ASSERT_EQ("", style.getName());
    ASSERT_EQ(13.3, style.getDefaultZoom());

    style.setJSON(R"STYLE({"pitch": 60})STYLE");
    ASSERT_EQ("", style.getName());
    ASSERT_EQ(60, style.getDefaultPitch());

    style.setJSON(R"STYLE({"name": 23, "center": {}, "bearing": "north", "zoom": null, "pitch": "wide"})STYLE");
    ASSERT_EQ("", style.getName());
    ASSERT_EQ((LatLng{0, 0}), style.getDefaultLatLng());
    ASSERT_EQ(0, style.getDefaultBearing());
    ASSERT_EQ(0, style.getDefaultZoom());
    ASSERT_EQ(0, style.getDefaultPitch());
}

TEST(Style, DuplicateSource) {
    util::RunLoop loop;

    ThreadPool threadPool{ 1 };
    StubFileSource fileSource;
    Style style { threadPool, fileSource, 1.0 };

    style.setJSON(util::read_file("test/fixtures/resources/style-unused-sources.json"));

    style.addSource(std::make_unique<VectorSource>("sourceId", "mapbox://mapbox.mapbox-terrain-v2"));

    try {
        style.addSource(std::make_unique<VectorSource>("sourceId", "mapbox://mapbox.mapbox-terrain-v2"));
        FAIL() << "Should not have been allowed to add a duplicate source id";
    } catch (std::runtime_error) {
        // Expected
    }
}

TEST(Style, RemoveSourceInUse) {
    util::RunLoop loop;

    auto log = new FixtureLogObserver();
    Log::setObserver(std::unique_ptr<Log::Observer>(log));

    ThreadPool threadPool{ 1 };
    StubFileSource fileSource;
    Style style { threadPool, fileSource, 1.0 };

    style.setJSON(util::read_file("test/fixtures/resources/style-unused-sources.json"));

    style.addSource(std::make_unique<VectorSource>("sourceId", "mapbox://mapbox.mapbox-terrain-v2"));
    style.addLayer(std::make_unique<LineLayer>("layerId", "sourceId"));

    // Should not remove the source
    auto removed = style.removeSource("sourceId");
    ASSERT_EQ(nullptr, removed);
    ASSERT_NE(nullptr, style.getSource("sourceId"));

    const FixtureLogObserver::LogMessage logMessage {
            EventSeverity::Warning,
            Event::General,
            int64_t(-1),
            "Source 'sourceId' is in use, cannot remove",
    };

    EXPECT_EQ(log->count(logMessage), 1u);
}
