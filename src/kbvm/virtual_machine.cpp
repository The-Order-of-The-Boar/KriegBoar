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

void KVirtualMachine::eq_number(const Instruction& instruction)
{
   const bool result = this->get_number(instruction.src1) == this->get_number(instruction.src2);
   this->set(instruction.dest, result);
}

void KVirtualMachine::eq_bool(const Instruction& instruction)
{
    const bool result = this->get_bool(instruction.src1) == this->get_bool(instruction.src2);
    this->set(instruction.dest, result);
}

void KVirtualMachine::eq_string(const Instruction& instruction)
{
    const bool result = this->get_string(instruction.src1) == this->get_string(instruction.src2);
    this->set(instruction.dest, result);
}

void KVirtualMachine::eq(const Instruction& instruction)
{
    const auto& address = instruction.src1;
    switch (this->memory.at(address).type)
    {
        case MemoryType::Number:
            this->eq_number(instruction);
            break;
        case MemoryType::Bool:
            this->eq_bool(instruction);
            break;
        case MemoryType::String:
            this->eq_string(instruction);
            break;
    }
}

void KVirtualMachine::print(const Instruction& instruction)
{
    const auto& address = instruction.src1;
    switch (this->memory.at(address).type)
    {
        case MemoryType::Number:
            coutnl(this->get_number(address));
            break;
        case MemoryType::Bool:
            coutnl(this->get_bool(address));
            break;
        case MemoryType::String:
            coutnl(this->get_string(address));
            break;
    }
}

void KVirtualMachine::execute_instruction(const Instruction& instruction)
{

    switch (instruction.type)
    {
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
        {
            this->eq(instruction);
        }
        case InstructionType::EqNumber:
            this->eq_number(instruction);
            break;
        case InstructionType::EqBool:
            this->eq_bool(instruction);
            break;
        case InstructionType::EqString:
            this->eq_string(instruction);
            break;
        case InstructionType::Neq:
            break;
        case InstructionType::Lt:
        {
            const auto result = this->get_number(instruction.src1) < this->get_number(instruction.src2);
            this->set(instruction.dest, result);
            break;
        }
        case InstructionType::Gt:
        {
            const auto result = this->get_number(instruction.src1) > this->get_number(instruction.src2);
            this->set(instruction.dest, result);
            break;
        }
        case InstructionType::Lte:
        {
            const auto result = this->get_number(instruction.src1) <= this->get_number(instruction.src2);
            this->set(instruction.dest, result);
            break;
        }
        case InstructionType::Gte:
        {
            const auto result = this->get_number(instruction.src1) >= this->get_number(instruction.src2);
            this->set(instruction.dest, result);
            break;
        }
        case InstructionType::And:
        {
            const auto result = this->get_bool(instruction.src1) && this->get_bool(instruction.src2);
            this->set(instruction.dest, result);
        }
        case InstructionType::Or:
        {
            const auto result = this->get_bool(instruction.src1) || this->get_bool(instruction.src2);
            this->set(instruction.dest, result);
        }
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
        case InstructionType::Print:
            this->print(instruction);
            break;
        case InstructionType::PrintNumber:
            coutnl(this->get_number(instruction.src1));
            break;
        case InstructionType::PrintBool:
            coutnl(this->get_bool(instruction.src1));
            break;
        case InstructionType::PrintString:
            coutnl(this->get_string(instruction.src1));
            break;
        case InstructionType::Branch:
            this->program_counter = instruction.label;
            break;
        case InstructionType::BranchIf:
            if(this->get_bool(instruction.src1)) this->program_counter = instruction.label;
            break;
    }
}