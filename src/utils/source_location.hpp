#pragma once

// builtin
#include <cstdint>
#include <ostream>
#include <string_view>

// extern
#include <fmt/ostream.h>


class SourceLocation {
public:

    std::string_view const filename;
    uint64_t line;

public:

    explicit SourceLocation(std::string_view _filename = __builtin_FILE(), uint64_t _line = __builtin_LINE()):
        filename{_filename}, line{_line}
    {
    }

    friend std::ostream& operator<<(std::ostream& os, SourceLocation const& sloc)
    {
        // TODO: comparar o path do filename com o path de onde o processo foi chamado
        //       para subtrair a igualdade entre eles. dessa forma evitamos que o output fique sujo
        //       ex:
        //          filename: "/home/foo/prog/bar.cpp"
        //          path atual: "/home/foo/prog"
        //          resultado: "bar.cpp" ou "./bar.cpp"

        return os << "(" << sloc.filename << ":" << sloc.line << ")";
    }
};

template <>
struct fmt::formatter<SourceLocation> : ostream_formatter {};
