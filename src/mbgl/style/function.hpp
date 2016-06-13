#pragma once

#include <vector>
#include <utility>

namespace mbgl {

template <typename T>
class Function {
public:
    using Stop = std::pair<float, T>;
    using Stops = std::vector<Stop>;

    explicit Function(const T& constant)
        : stops({{ 0, constant }}) {}

    explicit Function(const Stops& stops_, float base_)
        : base(base_), stops(stops_) {}

    float getBase() const { return base; }
    const std::vector<std::pair<float, T>>& getStops() const { return stops; }

private:
    float base = 1;
    std::vector<std::pair<float, T>> stops;
};

} // namespace mbgl
