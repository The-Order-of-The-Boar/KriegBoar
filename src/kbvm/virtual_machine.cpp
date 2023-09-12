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
    return this->memory.at(address).var.number_var;
}

inline bool KVirtualMachine::get_bool(const std::string& address) const
{
    return this->memory.at(address).var.bool_var;
}

inline const std::string& KVirtualMachine::get_string(const std::string& address) const
{
    return this->memory.at(address).var.string_var;
}

inline void KVirtualMachine::set(const std::string& address, const int value)
{
    this->memory[address].type = MemoryType::Number;
    this->memory[address].var.number_var = value;
}

inline void KVirtualMachine::set(const std::string& address, const bool value)
{
    this->memory[address].type = MemoryType::Bool;
    this->memory[address].var.bool_var = value;
}

inline void KVirtualMachine::set(const std::string& address, const std::string value)
{
    this->memory[address].type = MemoryType::String;
    this->memory[address].var.string_var = value;
}

void KVirtualMachine::add_number(const Instruction& instruction)
{
    const auto result = this->get_number(instruction.src1) + this->get_number(instruction.src2);
    this->set(instruction.dest, result);
}

void KVirtualMachine::add_string(const Instruction& instruction)
{
    const auto result = this->get_string(instruction.src1) + this->get_string(instruction.src2);
    this->set(instruction.dest, result);
}

void KVirtualMachine::add_number_string(const Instruction& instruction)
{
    const auto result = std::to_string(this->get_number(instruction.src1)) + this->get_string(instruction.src2);
    this->set(instruction.dest, result);
}

void KVirtualMachine::add_string_number(const Instruction& instruction)
{
    const auto result = this->get_string(instruction.src1) + std::to_string(this->get_number(instruction.src2));
    this->set(instruction.dest, result);
}

void KVirtualMachine::add(const Instruction& instruction)
{
    const auto& src1 = this->memory.at(instruction.src1);
    const auto& src2 = this->memory.at(instruction.src2);

    if(src1.type == MemoryType::Number)
    {
        if(src2.type == MemoryType::Number) this->add_number(instruction);
        else                                this->add_number_string(instruction);
    }
    else
    {
        if(src2.type == MemoryType::Number) this->add_string_number(instruction);
        else                                this->add_string(instruction);
    }

}

void KVirtualMachine::execute_instruction(const Instruction& instruction)
{

    switch (instruction.type) {
        case InstructionType::Add:
            this->add(instruction);
            break;
        case InstructionType::AddNumber:
            this->add_number(instruction);
            break;
        case InstructionType::AddString:
            this->add_string(instruction);
            break;
        case InstructionType::AddNumberString:
            this->add_number_string(instruction);
            break;
        case InstructionType::AddStringNumber:
            this->add_string_number(instruction);
            break;
        case InstructionType::Sub:
        {
            const auto result= this->get_number(instruction.src1) - this->get_number(instruction.src2);
            this->set(instruction.dest, result);
            break;
        }
        case InstructionType::Mul:
        {
            const auto result = this->get_number(instruction.src1) * this->get_number(instruction.src2);
            this->set(instruction.dest, result);
            break;
        }
        case InstructionType::Div:
        {
            const auto result = this->get_number(instruction.src1) / this->get_number(instruction.src2);
            this->set(instruction.dest, result);
            break;
        }
        case InstructionType::Rem:
        {
            const auto result= this->get_number(instruction.src1) % this->get_number(instruction.src2);
            this->set(instruction.dest, result);
            break;
        }
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
            this->program_counter = instruction.label;
            break;
        case InstructionType::BranchIf:
            if(this->get_bool(instruction.src1)) this->program_counter = instruction.label;
            break;
    }
}