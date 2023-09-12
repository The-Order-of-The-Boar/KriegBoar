#pragma once

// builtin
#include <string>
#include <vector>
#include <cstdint>
#include <memory>



struct Expression {};



struct Number: public Expression {

    int32_t value;
};

struct String: public Expression {

    std::string value;
};

struct Bool: public Expression {

    bool value;
};

struct Var: public Expression {

    std::string name;
};



struct FunctionCall: public Expression {

    std::unique_ptr<Expression> callee;
    std::vector<std::unique_ptr<Expression>> args;
};

struct NativeFunctionCall: public Expression {

    std::string name;
    std::unique_ptr<Expression> arg;
};

struct Function: public Expression {

    std::vector<std::string> parameters;
    std::unique_ptr<Expression> body;
};

struct Let: public Expression {

    std::string name;
    std::unique_ptr<Expression> value;
    std::unique_ptr<Expression> next;
};

struct If: public Expression {

    std::unique_ptr<Expression> cond_expr;
    std::unique_ptr<Expression> body;
    std::unique_ptr<Expression> else_body;
};

struct Tuple: public Expression {

    std::unique_ptr<Expression> first;
    std::unique_ptr<Expression> second;
};

enum class BinaryOprt {
    Add, Sub, Mul, Div, Rem,
    Eq, Neq, Lt, Gt, Lte, Gte,
    And, Or
};

struct Binary: public Expression {

    BinaryOprt oprt;
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
};
