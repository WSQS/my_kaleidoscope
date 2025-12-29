#include <array>
#include <string_view>
#include <tuple>
#include "sob.hpp"

struct GxxContext
{
    static constexpr std::string_view cxx{"g++"};
    static constexpr sopho::StaticString obj_prefix{" -o "};
    static constexpr sopho::StaticString obj_postfix{".o"};
    static constexpr sopho::StaticString bin_prefix{" -o "};
    static constexpr sopho::StaticString build_prefix{"build/"};
    static constexpr std::array<std::string_view, 1> ldflags{"`llvm-config --cxxflags --ldflags --system-libs --libs all`"};
};

struct ClContext
{
    static constexpr std::string_view cxx{"cl"};
    static constexpr sopho::StaticString obj_prefix{" /Fo:"};
    static constexpr sopho::StaticString obj_postfix{".obj"};
    static constexpr sopho::StaticString bin_prefix{" /Fe:"};
    static constexpr sopho::StaticString build_prefix{"build/"};
    static constexpr std::array<std::string_view, 1> cxxflags{"/std:c++17"};
};
struct SobSource
{
    static constexpr sopho::StaticString source{"sob.cpp"};
};
struct Sob
{
    using Dependent = std::tuple<SobSource>;
    static constexpr sopho::StaticString target{"sob"};
};
struct ToySource
{
    static constexpr sopho::StaticString source{"toy.cpp"};
};
struct Toy
{
    using Dependent = std::tuple<ToySource>;
    static constexpr sopho::StaticString target{"toy"};
};

#if defined(_MSC_VER)
using CxxContext = ClContext;
#elif defined(__GNUC__)
using CxxContext = GxxContext;
#else
#endif

int main(int argc, char **argv)
{
    sopho::CxxToolchain<CxxContext>::CxxBuilder<Sob>::build();
    sopho::CxxToolchain<CxxContext>::CxxBuilder<Toy>::build();
    return 0;
}
