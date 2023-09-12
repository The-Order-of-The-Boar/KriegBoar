
#include "virtual_machine.h"

#include "../code/code.hpp"

int main()
{
    auto instructions = std::vector<Instruction>
    {
            //Variable Declaration
        Instruction{.type = InstructionType::LetBool, .dest = "b1", .imm_bool = true},
        Instruction{.type = InstructionType::LetNumber, .dest = "n1", .imm_number = 666},
        Instruction{.type = InstructionType::LetNumber, .dest = "n2", .imm_number = 2},
        Instruction{.type = InstructionType::LetString, .dest = "s1", .imm_string = "BOAR4EVER"},
        Instruction{.type = InstructionType::LetString, .dest = "s2", .imm_string = "!!!"},


            // Specific type print
        Instruction{.type = InstructionType::PrintBool, .src1 = "b1" },
        Instruction{.type = InstructionType::PrintNumber, .src1 = "n1"},
        Instruction{.type = InstructionType::PrintNumber, .src1 = "n2"},
        Instruction{.type = InstructionType::PrintString, .src1 = "s1"},
        Instruction{.type = InstructionType::PrintString, .src1 = "s2"},

            // Arithmetic specific type operations
        Instruction{.type = InstructionType::AddNumber, .dest = "d1", .src1 = "n1", .src2 = "n2"}, // = 668
        Instruction{.type = InstructionType::PrintNumber, .src1 = "d1"},

        Instruction{.type = InstructionType::Div, .dest = "d2", .src1 = "n1", .src2 = "n2"}, // = 333
        Instruction{.type = InstructionType::PrintNumber, .src1 = "d2"},

        Instruction{.type = InstructionType::Mul, .dest = "d3", .src1 = "n1", .src2 = "n2"}, // = 1332
        Instruction{.type = InstructionType::PrintNumber, .src1 = "d3"},

        Instruction{.type = InstructionType::Rem, .dest = "d4", .src1 = "n1", .src2 = "n2"}, // = 0
        Instruction{.type = InstructionType::PrintNumber, .src1 = "d4"},

        Instruction{.type = InstructionType::AddStringNumber, .dest = "d6", .src1 = "s1", .src2 = "n1"}, // "BOAR4EVER666"
        Instruction{.type = InstructionType::PrintString, .src1 = "d6"},

        Instruction{.type = InstructionType::AddNumberString, .dest = "d7", .src1 = "n1", .src2 = "s1"}, // "666BOAR4EVER"
        Instruction{.type = InstructionType::PrintString, .src1 = "d7"},

        Instruction{.type = InstructionType::AddString, .dest = "d8", .src1 = "s1", .src2 = "s2"}, // "BOAR4EVER!!!
        Instruction{.type = InstructionType::PrintString, .src1 = "d8"},

            // Add generic type operations
        Instruction{.type = InstructionType::Add, .dest = "d9", .src1 = "n2", .src2 = "n1"}, // 668
        Instruction{.type = InstructionType::PrintNumber, .src1 = "d9"},

        Instruction{.type = InstructionType::Add, .dest = "d10", .src1 = "n1", .src2 = "s2"}, // "666!!!"
        Instruction{.type = InstructionType::PrintString, .src1 = "d10"},

        Instruction{.type = InstructionType::Add, .dest = "d11", .src1 = "s2", .src2 = "n2"}, // "!!!2"
        Instruction{.type = InstructionType::PrintString, .src1 = "d11"},

        Instruction{.type = InstructionType::Add, .dest = "d12", .src1 = "s2", .src2 = "s1"}, // "!!!BOAR4EVER"
        Instruction{.type = InstructionType::PrintString, .src1 = "d12"},

    };

    KVirtualMachine virtual_machine{Code{instructions}};
}