#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <istream>
#include <iterator>
#include <ostream>

#include <Dimensions.hh>

template <Dimensions dim>
class Matrix {
private:
    using Element = std::int32_t;
    using Row = std::array<Element, dim.x>;
    using Plane = std::array<Row, dim.y>;
    using Data = std::array<Plane, dim.z>;

    Data data {};

    friend auto operator>>(std::istream& in, Matrix<dim>& matrix) -> std::istream& {
        for (auto& plane : matrix.data) {
            for (auto& row : plane) {
                std::copy_n(std::istream_iterator<typename Matrix<dim>::Element>(in), dim.x, std::begin(row));
            }
        }

        return in;
    }

    friend auto operator<<(std::ostream& out, Matrix<dim> const& matrix) -> std::ostream& {
        for (auto const& plane : matrix.data) {
            out << '\n';
            for (auto const& row : plane) {
                std::copy(std::cbegin(row), std::cend(row),
                          std::ostream_iterator<typename Matrix<dim>::Element>(out, " "));
                out << '\n';
            }
        }

        return out;
    }
};
