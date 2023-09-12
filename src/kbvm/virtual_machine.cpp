#include "virtual_machine.h"

#include <iostream>

KVirtualMachine::KVirtualMachine(const Code& code)
{
    auto& instructions = code.instructions;
    const size_t instruction_size = instructions.size();

    while(this->program_counter < instruction_size)
    {
        auto cur_instruction = instructions[this->program_counter];
        this->program_counter += 1;

        this->execute_instruction(cur_instruction);
    }
}

void KVirtualMachine::execute_instruction(const Instruction& instruction)
{
    switch (instruction.type) {
        case InstructionType::Add:
            break;
        case InstructionType::AddNumber:
            break;
        case InstructionType::AddString:
            break;
        case InstructionType::AddNumberString:
            break;
        case InstructionType::Sub:
            break;
        case InstructionType::Mul:
            break;
        case InstructionType::Div:
            break;
        case InstructionType::Rem:
            break;
        case InstructionType::Eq:
            break;
        case InstructionType::Neq:
            break;
        case InstructionType::Lt:
            break;
        case InstructionType::Gt:
            break;
        case InstructionType::Lte:
            break;
        case InstructionType::Gte:
            break;
        case InstructionType::And:
            break;
        case InstructionType::Or:
            break;
        case InstructionType::LetNumber:
            break;
        case InstructionType::LetString:
            break;
        case InstructionType::LetBool:
            break;
        case InstructionType::CreateTuple:
            break;
        case InstructionType::First:
            break;
        case InstructionType::Second:
            break;
        case InstructionType::Print:
            std::cout << "No One is Higher Than The Boar!!!" << std::endl;
            break;
        case InstructionType::Branch:
            break;
        case InstructionType::BranchIf:
            break;
    }
}