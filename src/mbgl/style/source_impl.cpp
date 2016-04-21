#include <mbgl/style/source_impl.hpp>

namespace mbgl {
namespace style {

Source::Impl::Impl(SourceType type_, std::string id_)
    : type(type_),
      id(std::move(id_)) {
}

void Source::Impl::limitMaxZoom(uint8_t) {
}
    
} // namespace style
} // namespace mbgl
