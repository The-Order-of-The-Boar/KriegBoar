#pragma once

// builtin
#include <string>
#include <utility>
#include <vector>
#include <cstdint>
#include <optional>
#include <memory>

// local
#include <assert.hpp>



enum class ValueTypeType {

    Any,
    Number,
    String,
    Bool,
    Closure,
    Tuple,
};

struct ValueType {

public:

    ValueTypeType type;
    std::optional<std::pair<std::unique_ptr<ValueType>, std::unique_ptr<ValueType>>> tuple_fields;
    std::optional<std::vector<ValueType>> closure_params;
    std::optional<std::unique_ptr<ValueType>> closure_return_value;

public:
    
    static ValueType make_simple(ValueTypeType type) {

        debug_assert(type != ValueTypeType::Closure);
        debug_assert(type != ValueTypeType::Tuple);
        return ValueType{type, std::nullopt, std::nullopt, std::nullopt};
    }

    static ValueType make_closure(std::vector<ValueType> param_types, ValueType return_value) {

        return ValueType{ValueTypeType::Closure, std::nullopt, std::move(param_types), std::make_unique<ValueType>(return_value)};
    }
    
    static ValueType make_tuple(ValueType field1, ValueType field2) {

        auto field1_ptr = std::make_unique<ValueType>(field1);
        auto field2_ptr = std::make_unique<ValueType>(field2);
        auto tuple = std::make_pair(std::move(field1_ptr), std::move(field2_ptr));

        return ValueType{ValueTypeType::Tuple, std::move(tuple), std::nullopt, std::nullopt};
    }

public:

    ValueType(decltype(type) _type, decltype(tuple_fields) _tuple_fields, decltype(closure_params) _closure_params, decltype(closure_return_value) _closure_return_value)
    : type(_type), tuple_fields(std::move(_tuple_fields)), closure_params(std::move(_closure_params)), closure_return_value(std::move(_closure_return_value)) {}

    ValueType(ValueType const& other) {

        *this = other;
    }

    ValueType& operator=(ValueType const& other) {

        this->type = other.type;
        
        if (other.type == ValueTypeType::Tuple) {

            auto field1_ptr = std::make_unique<ValueType>(*other.tuple_fields->first);
            auto field2_ptr = std::make_unique<ValueType>(*other.tuple_fields->second);
            this->tuple_fields = std::make_pair(std::move(field1_ptr), std::move(field2_ptr));
        }
        else if (other.type == ValueTypeType::Closure) {

            this->closure_params = std::vector<ValueType>{};
            for (auto& param: other.closure_params.value())
                this->closure_params->push_back(param);
        }

        return *this;
    }

    friend bool operator==(ValueType const& a, ValueType const& b) {

        if (a.type != b.type)
            return false;

        if (a.type == ValueTypeType::Tuple)
            return a.tuple_fields == b.tuple_fields;
        else if (a.type == ValueTypeType::Closure)
            return a.closure_params == b.closure_params;
        
        return true;
    }
};

inline ValueType const VT_ANY = ValueType::make_simple(ValueTypeType::Any);
inline ValueType const VT_NUMBER = ValueType::make_simple(ValueTypeType::Number);
inline ValueType const VT_STRING = ValueType::make_simple(ValueTypeType::String);
inline ValueType const VT_BOOL = ValueType::make_simple(ValueTypeType::Bool);
