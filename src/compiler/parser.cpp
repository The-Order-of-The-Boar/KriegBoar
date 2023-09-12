// header
#include "parser.hpp"

// builtin
#include <unordered_map>



void expect_from_input(bool value, SourceLocation sloc = SourceLocation{})
{
    always_assert(value, "invalid input or internal error", sloc);
}

void expect_kind(nlohmann::json const& input, std::string const& expected_kind)
{
    expect_from_input(input.is_object());
    expect_from_input(input.contains("kind"));
    expect_from_input(input["kind"].is_string());
    std::string kind = input["kind"];
    expect_from_input(kind == expected_kind);
}

std::unique_ptr<Expression> parse_expression(nlohmann::json const& input);



std::string parse_parameter(nlohmann::json const& input)
{
    expect_from_input(input.is_object());
    expect_from_input(input.contains("text"));
    expect_from_input(input["text"].is_string());
    return input["text"];
}

Number parse_number(nlohmann::json const& input)
{
    expect_kind(input, "Int");

    expect_from_input(input.contains("value"));
    expect_from_input(input["value"].is_number());
    return Number{.value = input["value"]};
}

String parse_string(nlohmann::json const& input)
{
    expect_kind(input, "Str");

    expect_from_input(input.contains("value"));
    expect_from_input(input["value"].is_string());
    return String{.value = input["value"]};
}

Bool parse_bool(nlohmann::json const& input)
{
    expect_kind(input, "Bool");

    expect_from_input(input.contains("value"));
    expect_from_input(input["value"].is_boolean());
    return Bool{.value = input["value"]};
}

Var parse_var(nlohmann::json const& input)
{
    expect_kind(input, "Var");

    expect_from_input(input.contains("text"));
    expect_from_input(input["text"].is_string());
    return Var{.name = input["text"]};
}

FunctionCall parse_function_call(nlohmann::json const& input)
{
    expect_kind(input, "Call");

    // callee
    expect_from_input(input.contains("callee"));
    auto callee = parse_expression(input["callee"]);

    // args
    expect_from_input(input.contains("arguments"));
    expect_from_input(input["arguments"].is_array());

    std::vector<std::unique_ptr<Expression>> args;
    for (const auto& value: input["arguments"])
        args.push_back(parse_expression(value));

    return FunctionCall{.callee = std::move(callee), .args = std::move(args)};
}

Function parse_function(nlohmann::json const& input)
{
    expect_kind(input, "Function");

    // parameters
    expect_from_input(input.contains("parameters"));
    expect_from_input(input["parameters"].is_array());

    std::vector<std::string> parameters;
    for (auto const& value: input["parameters"])
        parameters.push_back(parse_parameter(value));

    // body
    expect_from_input(input.contains("value"));
    auto body = parse_expression(input["value"]);

    return Function{.parameters = parameters, .body = std::move(body)};
}

Let parse_let(nlohmann::json const& input)
{
    expect_kind(input, "Let");

    // name
    expect_from_input(input.contains("name"));
    auto name = parse_parameter(input["name"]);

    // value
    expect_from_input(input.contains("value"));
    auto value = parse_expression(input["value"]);

    // next
    expect_from_input(input.contains("next"));
    auto next = parse_expression(input["next"]);

    return Let{.name = name, .value = std::move(value), .next = std::move(next)};
}

If parse_if(nlohmann::json const& input) {

    expect_kind(input, "If");

    // condition
    expect_from_input(input.contains("condition"));
    auto condition = parse_expression(input["condition"]);

    // body
    expect_from_input(input.contains("then"));
    auto body = parse_expression(input["then"]);

    // else body
    expect_from_input(input.contains("otherwise"));
    auto else_body = parse_expression(input["otherwise"]);

    return If{.cond_expr = std::move(condition), .body = std::move(body), .else_body = std::move(else_body)};
}

Tuple parse_tuple(nlohmann::json const& input) {

    expect_kind(input, "Tuple");

    expect_from_input(input.contains("first"));
    auto first = parse_expression(input["first"]);

    expect_from_input(input.contains("second"));
    auto second = parse_expression(input["second"]);

    return Tuple{.first = std::move(first), .second = std::move(second)};
}

Binary parse_binary(nlohmann::json const& input) {

    expect_kind(input, "Binary");

    // left
    expect_from_input(input.contains("lhs"));
    auto left = parse_expression(input["lhs"]);

    // right
    expect_from_input(input.contains("rhs"));
    auto right = parse_expression(input["rhs"]);

    // repr_oprt
    expect_from_input(input.contains("op"));
    expect_from_input(input["op"].is_string());
    std::string repr_oprt = input["op"];

    static std::unordered_map<std::string, BinaryOprt> const oprt_map {
        {"Add", BinaryOprt::Add},
        {"Sub", BinaryOprt::Sub},
        {"Mul", BinaryOprt::Mul},
        {"Div", BinaryOprt::Div},
        {"Rem", BinaryOprt::Rem},
        {"Eq",  BinaryOprt::Eq},
        {"Neq", BinaryOprt::Neq},
        {"Lt",  BinaryOprt::Lt},
        {"Gt",  BinaryOprt::Gt},
        {"Lte", BinaryOprt::Lte},
        {"Gte", BinaryOprt::Gte},
        {"And", BinaryOprt::Add},
        {"Or",  BinaryOprt::Or},
    };

    expect_from_input(oprt_map.contains(repr_oprt));
    auto oprt = oprt_map.at(repr_oprt);

    return Binary{.oprt = oprt, .left = std::move(left), .right = std::move(right)};
}

NativeFunctionCall parse_native_function_call(nlohmann::json const& input) {

    expect_from_input(input.contains("kind"));
    expect_from_input(input["kind"].is_string());
    std::string func_name = input["kind"];

    expect_from_input(input.contains("value"));
    auto arg = parse_expression(input["value"]);

    return NativeFunctionCall{.name = func_name, .arg = std::move(arg)};
}



std::unique_ptr<Expression> parse_expression(nlohmann::json const& input)
{
    expect_from_input(input.is_object());
    expect_from_input(input.contains("kind"));
    std::string kind = input["kind"];

#define DeclLambdaWrapper(func_name)                                                                                   \
    [](nlohmann::json const& input) { return std::make_unique<Expression>(func_name(input)); }

    static std::unordered_map<std::string, std::unique_ptr<Expression> (*)(nlohmann::json const&)> const kind_map{
        {"Int", DeclLambdaWrapper(parse_number)},
        {"Str", DeclLambdaWrapper(parse_string)},
        {"Bool", DeclLambdaWrapper(parse_bool)},
        {"Var", DeclLambdaWrapper(parse_var)},
        {"Call", DeclLambdaWrapper(parse_function_call)},
        {"Function", DeclLambdaWrapper(parse_function)},
        {"Let", DeclLambdaWrapper(parse_let)},
        {"If", DeclLambdaWrapper(parse_if)},
        {"Tuple", DeclLambdaWrapper(parse_tuple)},
        {"Binary", DeclLambdaWrapper(parse_binary)},

        {"First", DeclLambdaWrapper(parse_native_function_call)},
        {"Second", DeclLambdaWrapper(parse_native_function_call)},
        {"Print", DeclLambdaWrapper(parse_native_function_call)},
    };

#undef DeclLambdaWrapper

    expect_from_input(kind_map.contains(kind));
    return kind_map.at(kind)(input);
}

std::unique_ptr<Expression> parse_tree_from_json(nlohmann::json const& input)
{
    expect_from_input(input.is_object());
    expect_from_input(input.contains("expression"));
    expect_from_input(input["expression"].is_object());
    return parse_expression(input["expression"]);
}
