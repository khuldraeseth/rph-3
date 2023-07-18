#pragma once

#include <cstdint>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>

struct Dimensions {
    std::uint16_t z {};
    std::uint16_t y {};
    std::uint16_t x {};
};

inline auto operator>>(std::istream& in, Dimensions& dim) -> std::istream& {
    return in >> dim.z >> dim.y >> dim.x;
}

inline auto operator<<(std::ostream& out, Dimensions dim) -> std::ostream& {
    return out << dim.z << ' ' << dim.y << ' ' << dim.x;
}

inline auto repr(Dimensions const& dim) -> std::string {
    std::ostringstream out {};
    out << "Dimensions { .z = " << dim.z << ", .y = " << dim.y << ", .x = " << dim.x << " }";
    return out.str();
}
