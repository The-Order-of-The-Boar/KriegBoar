
#include "virtual_machine.h"

#include "../code/code.hpp"

int main()
{
    auto instructions = std::vector<Instruction>
    {
        Instruction{.type = InstructionType::LetBool, .dest = "b1", .imm_bool = true},
        Instruction{.type = InstructionType::PrintBool, .src1 = "b1" },
        Instruction{.type = InstructionType::LetNumber, .dest = "n1", .imm_number = 666},
        Instruction{.type = InstructionType::PrintNumber, .src1 = "n1"},
        Instruction{.type = InstructionType::LetString, .dest = "s1", .imm_string = "BOAR4EVER"},
        Instruction{.type = InstructionType::PrintString, .src1 = "s1"},

    };

    KVirtualMachine virtual_machine{Code{instructions}};
}