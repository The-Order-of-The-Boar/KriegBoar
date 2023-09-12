#pragma once

// builtin
#include <vector>
#include <string>
#include <cstdint>
#include <cstddef>



enum class InstructionType {

    Add, AddNumber, AddString, AddNumberString, AddStringNumber,
    Sub,
    Mul, Div, Rem,
    Eq, Neq,
    Lt, Gt,
    Lte, Gte,
    And, Or,
    LetNumber, LetString, LetBool,
    CreateTuple, First, Second,
    Print, PrintNumber, PrintString, PrintBool,
    Branch, BranchIf
};


using Address = std::string;

struct Instruction {

    const InstructionType type;
    const Address dest;
    const Address src1;
    const Address src2;
    const size_t label;

    const bool imm_bool;
    const Address imm_string;
    const int32_t imm_number;

};

struct Code {

    const std::vector<Instruction> instructions;
};