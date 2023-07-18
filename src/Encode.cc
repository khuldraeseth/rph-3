#include <iostream>
#include <string>

#include <Dimensions.hh>
#include <unistd.h>

#include <sys/wait.h>

[[noreturn]] auto main() -> int {
    auto name = std::string {};
    std::cin >> name;

    auto filename = std::string {};
    std::cin >> filename;

    auto dimensions = Dimensions {};
    std::cin >> dimensions;

    switch (fork()) {
    case 0:
        // clang-format off
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
        execlp(
            "clang++",
            "clang++",
            "--std=c++20",
            "-Wall", "-Wextra", "-Wpedantic", "-Werror",
            "-Os",
            "-Iinclude",
            "-o", "/tmp/phase2",
            "src/TypedEncode.cc",
            ("-DNAME=\"" + name + "\"").c_str(),
            ("-DFILENAME=\"" + filename + "\"").c_str(),
            ("-DDIMENSIONS=" + repr(dimensions)).c_str(),
            nullptr
        );
        // clang-format on
    default:
        wait(nullptr);
        std::cin.sync();
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
        execl("/tmp/phase2", "/tmp/phase2", nullptr);
    }
}
