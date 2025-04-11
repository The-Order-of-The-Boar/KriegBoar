#pragma once

// builtin
#include <optional>
#include <string>

// local
#include "source_location.hpp"



void assert_enable_exception_mode();
void debug_assert(bool result, std::string const& message = "", SourceLocation location = SourceLocation{});
void always_assert(bool result, std::string const& message = "", SourceLocation location = SourceLocation{});
