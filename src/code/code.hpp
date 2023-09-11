#pragma once

// builtin
#include <vector>
#include <string>
#include <cstdint>
#include <cstddef>



enum class InstructionType {

    Add, AddNumber, AddString, AddNumberString,
    Sub,
    Mul, Div, Rem,
    Eq, Neq,
    Lt, Gt,
    Lte, Gte,
    And, Or,
    LetNumber, LetString, LetBool,
    CreateTuple, First, Second,
    Print,
    Branch, BranchIf
};


using Address = std::string;

struct Instruction {

    const InstructionType type;
    const Address dest;
    const Address src1;
    const Address src2;
    const size_t label;

    union {
        const bool imm_bool;
        const std::string imm_string;
        const int32_t imm_number;
    };
};

struct Code {

    const std::vector<Instruction> code;
};