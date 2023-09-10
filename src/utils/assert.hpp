#pragma once

// builtin
#include <optional>
#include <string>

// local
#include "source_location.hpp"



// extern bool const assert_exception;
inline bool const assert_exception = false;

void debug_assert(bool result, std::string const& message = "", SourceLocation location = SourceLocation{});
void always_assert(bool result, std::string const& message = "", SourceLocation location = SourceLocation{});
