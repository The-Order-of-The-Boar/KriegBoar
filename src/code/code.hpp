#pragma once

// builtin
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>



enum class InstructionType {
    Add,
    AddNumber,
    AddString,
    AddNumberString,
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
    Or,
    LetNumber,
    LetString,
    LetBool,
    CreateTuple,
    First,
    Second,
    Print,
    Branch,
    BranchIf
};


using Address = std::string;

struct Instruction {
    InstructionType const type;
    Address const dest;
    Address const src1;
    Address const src2;
    size_t const label;

    union {
        bool const imm_bool;
        std::string const imm_string;
        int32_t const imm_number;
    };
};

struct Code {
    std::vector<Instruction> const code;
};