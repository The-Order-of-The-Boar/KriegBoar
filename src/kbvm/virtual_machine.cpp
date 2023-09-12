#include "virtual_machine.h"

#include <iostream>

KVirtualMachine::KVirtualMachine(const Code& code)
{
    const auto& instructions = code.instructions;
    const size_t instruction_size = instructions.size();

    while(this->program_counter < instruction_size)
    {
        auto& cur_instruction = instructions[this->program_counter];
        this->program_counter += 1;

        this->execute_instruction(cur_instruction);
    }
}

inline int KVirtualMachine::get_number(const std::string& address) const
{
    return this->memory.at(address).int_var;
}

inline bool KVirtualMachine::get_bool(const std::string& address) const
{
    return this->memory.at(address).bool_var;
}

inline const std::string& KVirtualMachine::get_string(const std::string& address) const
{
    return this->memory.at(address).string_var;
}

inline void KVirtualMachine::set(const std::string& address, const int value)
{
    this->memory[address].int_var = value;
}

inline void KVirtualMachine::set(const std::string& address, const bool value)
{
    this->memory[address].bool_var = value;
}

inline void KVirtualMachine::set(const std::string& address, const std::string value)
{
    this->memory[address].string_var = value;
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
            this->set(instruction.dest, instruction.imm_number);
            break;
        case InstructionType::LetString:
            this->set(instruction.dest, instruction.imm_string);
            break;
        case InstructionType::LetBool:
            this->set(instruction.dest, instruction.imm_bool);
            break;
        case InstructionType::CreateTuple:
            break;
        case InstructionType::First:
            break;
        case InstructionType::Second:
            break;
        case InstructionType::PrintNumber:
            std::cout << this->get_number(instruction.src1) << std::endl;
            break;
        case InstructionType::PrintBool:
            std::cout << this->get_bool(instruction.src1) << std::endl;
            break;
        case InstructionType::PrintString:
            std::cout << this->get_string(instruction.src1) << std::endl;
            break;
        case InstructionType::Branch:
            break;
        case InstructionType::BranchIf:
            break;
    }
}