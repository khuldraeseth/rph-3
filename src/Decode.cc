#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <span>
#include <string_view>

#include <Dimensions.hh>
#include <Matrix.hh>

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define EXTERN_BINARY(name, ext)                                              \
    extern char const* const _binary_build_##name##_##ext##_start;            \
    extern char const* const _binary_build_##name##_##ext##_end;              \
    [[maybe_unused]] inline static auto const name##Begin                     \
      = reinterpret_cast<char const*>(&_binary_build_##name##_##ext##_start); \
    [[maybe_unused]] inline static auto const name##End                       \
      = reinterpret_cast<char const*>(&_binary_build_##name##_##ext##_end);

// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
EXTERN_BINARY(name, txt)
// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
EXTERN_BINARY(matrix, bin)
// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
EXTERN_BINARY(timestamp, bin)

using Timestamp = std::chrono::duration<int>;

auto main(int argc, char const* const* argv) -> int {
    using std::literals::operator""sv;

    auto const args = std::span(argv, std::next(argv, argc));
    auto const verbose = args.size() > 1 and args[1] == "-v"sv;

    auto const owner = std::string_view(nameBegin, nameEnd);
    if (verbose) {
        std::cout << "Owner: " << owner << "\n";
    } else {
        std::cout << owner << "\n";
    }

    if (verbose) {
        std::cout << "Encoded matrix '" << args.front() << "'\n";
    } else {
        std::cout << args.front() << "\n";
    }

    if (verbose) {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
        auto const& timestamp = reinterpret_cast<Timestamp const&>(*timestampBegin);
        std::cout << "Timestamp: " << timestamp.count() << std::endl;
    }

    std::cout << DIMENSIONS << std::endl;

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    auto const& matrix = reinterpret_cast<Matrix<DIMENSIONS> const&>(*matrixBegin);
    std::cout << matrix << std::endl;

    return 0;
}
