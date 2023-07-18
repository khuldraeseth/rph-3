#include <chrono>
#include <fstream>
#include <iostream>
#include <ostream>

#include <Matrix.hh>
#include <unistd.h>

#include <sys/wait.h>

[[noreturn]] auto main() -> int {
    switch (fork()) {
    case 0:
        std::ofstream("build/name.txt") << NAME << std::flush;
        // clang-format off
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
        execlp(
            "ld", "ld",
            "-r",
            "-b", "binary",
            "-o", "build/name.o",
            "build/name.txt",
            nullptr
        );
        // clang-format on
    default:
        wait(nullptr);
    }

    switch (fork()) {
    case 0: {
        auto matrix = Matrix<DIMENSIONS> {};
        std::cin >> matrix;

        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
        std::ofstream("build/matrix.bin").write(reinterpret_cast<char const*>(&matrix), sizeof(matrix));
        // clang-format off
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
        execlp(
            "ld", "ld",
            "-r",
            "-b", "binary",
            "-o", "build/matrix.o",
            "build/matrix.bin",
            nullptr
        );
        // clang-format on
    }
    default:
        wait(nullptr);
    }

    switch (fork()) {
    case 0: {
        auto const now = std::chrono::system_clock::now();
        auto const timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
        std::ofstream("build/timestamp.bin").write(reinterpret_cast<char const*>(&timestamp), sizeof(timestamp));
        // clang-format off
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
        execlp(
            "ld", "ld",
            "-r",
            "-b", "binary",
            "-o", "build/timestamp.o",
            "build/timestamp.bin",
            nullptr
        );
        // clang-format on
    }
    default:
        wait(nullptr);
    }

    // clang-format off
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
    execlp(
        "clang++",
        "clang++",
        "--std=c++20",
        "-Wall", "-Wextra", "-Wpedantic", "-Werror",
        "-Os",
        "-Iinclude",
        "-o", FILENAME,
        "src/Decode.cc",
        "build/name.o",
        "build/matrix.o",
        "build/timestamp.o",
        ("-DDIMENSIONS=" + repr(DIMENSIONS)).c_str(),
        nullptr
    );
    // clang-format on
}
