#pragma once

// local
#include "tree.hpp"



class Traverser: public Visitor {

public:

    void visit(Number& number) override {

        // do nothing
    }

    void visit(String& string) override {

        // do nothing
    }

    void visit(Bool& a_bool) override {

        // do nothing
    }

    void visit(Var& var) override {

        // do nothing
    }

    void visit(FunctionCall& call) override {

        call.callee->accept(*this);

        for (auto& arg: call.args)
            arg->accept(*this);
    }

    void visit(NativeFunctionCall& call) override {

        call.arg->accept(*this);
    }

    void visit(Function& function) override {

        function.body->accept(*this);
    }

    void visit(Let& let) override {


    }

    void visit(If& an_if) override {

    }

    void visit(Tuple& tuple) override {

    }

    void visit(Binary& binary) override {

    }

};