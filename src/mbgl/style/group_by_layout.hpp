#pragma once

#include <vector>
#include <memory>

namespace mbgl {
namespace style {

class Layer;

std::vector<std::vector<std::unique_ptr<Layer>>> groupByLayout(std::vector<std::unique_ptr<Layer>>);

} // namespace style
} // namespace mbgl
