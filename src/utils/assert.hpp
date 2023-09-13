#pragma once

// builtin
#include <optional>
#include <string>

// local
#include "source_location.hpp"



extern bool const assert_exception;

void debug_assert(bool result, std::string const& message = "", SourceLocation location = SourceLocation{});
void always_assert(bool result, std::string const& message = "", SourceLocation location = SourceLocation{});
