#ifndef MBGL_TEXT_GLYPH_STORE
#define MBGL_TEXT_GLYPH_STORE

#include <mbgl/text/glyph.hpp>
#include <mbgl/text/glyph_set.hpp>
#include <mbgl/style/types.hpp>
#include <mbgl/util/exclusive.hpp>
#include <mbgl/util/noncopyable.hpp>
#include <mbgl/util/work_queue.hpp>

#include <exception>
#include <vector>
#include <set>
#include <string>
#include <unordered_map>

namespace mbgl {

class FileSource;
class GlyphPBF;

// The GlyphStore manages the loading and storage of Glyphs
// and creation of GlyphSet objects. The GlyphStore lives
// on the MapThread but can be queried from any thread.
class GlyphStore : private util::noncopyable {
public:
    class Observer {
    public:
        virtual ~Observer() = default;

        virtual void onGlyphsLoaded(const FontStack&, const GlyphRange&) {};
        virtual void onGlyphsError(const FontStack&, const GlyphRange&, std::exception_ptr) {};
    };

    GlyphStore(FileSource&);
    ~GlyphStore();

    util::exclusive<GlyphSet> getGlyphSet(const FontStack&);

    // Returns true if the set of GlyphRanges are available and parsed or false
    // if they are not. For the missing ranges, a request on the FileSource is
    // made and when the glyph if finally parsed, it gets added to the respective
    // GlyphSet and a signal is emitted to notify the observers. This method
    // can be called from any thread.
    bool hasGlyphRanges(const FontStack&, const std::set<GlyphRange>&);

    void setURL(const std::string &url) {
        glyphURL = url;
    }

    std::string getURL() const {
        return glyphURL;
    }

    void setObserver(Observer* observer);

private:
    void requestGlyphRange(const FontStack&, const GlyphRange&);

    FileSource& fileSource;
    std::string glyphURL;

    std::unordered_map<FontStack, std::map<GlyphRange, std::unique_ptr<GlyphPBF>>, FontStackHash> ranges;
    std::mutex rangesMutex;

    std::unordered_map<FontStack, std::unique_ptr<GlyphSet>, FontStackHash> glyphSets;
    std::mutex glyphSetsMutex;

    util::WorkQueue workQueue;

    Observer nullObserver;
    Observer* observer = &nullObserver;
};

} // namespace mbgl

#endif
