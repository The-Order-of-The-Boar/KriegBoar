#pragma once

// builtin
#include <cstdint>
#include <memory>
#include <string>
#include <vector>



struct Number;
struct String;
struct Bool;
struct Var;
struct FunctionCall;
struct NativeFunctionCall;
struct Function;
struct Let;
struct If;
struct Tuple;
struct Binary;


struct Visitor {
    virtual void visit(Number&) = 0;
    virtual void visit(String&) = 0;
    virtual void visit(Bool&) = 0;
    virtual void visit(Var&) = 0;
    virtual void visit(FunctionCall&) = 0;
    virtual void visit(NativeFunctionCall&) = 0;
    virtual void visit(Function&) = 0;
    virtual void visit(Let&) = 0;
    virtual void visit(If&) = 0;
    virtual void visit(Tuple&) = 0;
    virtual void visit(Binary&) = 0;
};

struct Expression {
    virtual void accept(Visitor&) = 0;
    virtual ~Expression() = default;
};



struct Number : public Expression {
public:

    int32_t value;

public:

    explicit Number(int32_t _value): value(_value) {}

    void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }
};

struct String : public Expression {
public:

    std::string value;

public:

    explicit String(std::string _value): value(std::move(_value)) {}

    void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }
};

struct Bool : public Expression {
public:

    bool value;

public:

    explicit Bool(bool _value): value(_value) {}

    void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }
};

struct Var : public Expression {
public:

    std::string name;

public:

    explicit Var(std::string _name): name(std::move(_name)) {}

    void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }
};



struct FunctionCall : public Expression {
public:

    std::unique_ptr<Expression> callee;
    std::vector<std::unique_ptr<Expression>> args;

public:

    FunctionCall(decltype(callee) _callee, decltype(args) _args): callee(std::move(_callee)), args(std::move(_args)) {}

    void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }
};

struct NativeFunctionCall : public Expression {
public:

    std::string name;
    std::unique_ptr<Expression> arg;

public:

    NativeFunctionCall(std::string _name, std::unique_ptr<Expression> _arg):
        name(std::move(_name)), arg(std::move(_arg))
    {
    }

    void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }
};

struct Function : public Expression {
public:

    std::vector<std::string> parameters;
    std::unique_ptr<Expression> body;

public:

    Function(std::vector<std::string> _params, std::unique_ptr<Expression> _body):
        parameters(std::move(_params)), body(std::move(_body))
    {
    }

    void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }
};

struct Let : public Expression {
public:

    std::string name;
    std::unique_ptr<Expression> value;
    std::unique_ptr<Expression> next;

public:

    Let(std::string _name, std::unique_ptr<Expression> _value, std::unique_ptr<Expression> _next):
        name(std::move(_name)), value(std::move(_value)), next(std::move(_next))
    {
    }

    void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }
};

struct If : public Expression {
public:

    std::unique_ptr<Expression> cond_expr;
    std::unique_ptr<Expression> body;
    std::unique_ptr<Expression> else_body;

public:

    If(std::unique_ptr<Expression> _cond_expr, std::unique_ptr<Expression> _body,
       std::unique_ptr<Expression> _else_body):
        cond_expr(std::move(_cond_expr)),
        body(std::move(_body)), else_body(std::move(_else_body))
    {
    }

    void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }
};

struct Tuple : public Expression {
public:

    std::unique_ptr<Expression> first;
    std::unique_ptr<Expression> second;

public:

    Tuple(std::unique_ptr<Expression> _first, std::unique_ptr<Expression> _second):
        first(std::move(_first)), second(std::move(_second))
    {
    }

    void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }
};

enum class BinaryOprt {
    Add,
    Sub,
    Mul,
    Div,
    Rem,
    Eq,
    Neq,
    Lt,
    Gt,
    Lte,
    Gte,
    And,
    Or
};

struct Binary : public Expression {
public:

    BinaryOprt oprt;
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

public:

    Binary(BinaryOprt _oprt, std::unique_ptr<Expression> _left, std::unique_ptr<Expression> _right):
        oprt(_oprt), left(std::move(_left)), right(std::move(_right))
    {
    }

    void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }
};
