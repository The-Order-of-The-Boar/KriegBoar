#pragma once

// extern
#include <nlohmann/json.hpp>

// local
#include "tree.hpp"
#include <assert.hpp>



std::unique_ptr<Expression> parse_tree_from_json(nlohmann::json const& input);
