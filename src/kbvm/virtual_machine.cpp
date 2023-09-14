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

void KVirtualMachine::add_number(const Instruction& instruction)
{
    const auto result = this->get<int32_t>(instruction.src1) + this->get<int32_t>(instruction.src2);
    this->set(instruction.dest, result);
}

void KVirtualMachine::add_string(const Instruction& instruction)
{
    const auto result = this->get<std::string>(instruction.src1) + this->get<std::string>(instruction.src2);
    this->set(instruction.dest, result);
}

void KVirtualMachine::add_number_string(const Instruction& instruction)
{
    const auto result = std::to_string(this->get<int32_t>(instruction.src1)) + this->get<std::string>(instruction.src2);
    this->set(instruction.dest, result);
}

void KVirtualMachine::add_string_number(const Instruction& instruction)
{
    const auto result = this->get<std::string>(instruction.src1) + std::to_string(this->get<std::int32_t>(instruction.src2));
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

void KVirtualMachine::eq(const Instruction& instruction)
{
   const bool result = this->memory.at(instruction.src1).var == this->memory.at(instruction.src2).var;
   this->set(instruction.dest, result);
}

void KVirtualMachine::print(const std::string& address) const
{
    const auto& variable = this->memory.at(address).var;
    std::visit([](auto& var) {std::cout << var << std::endl;}, variable);
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
            const auto result= this->get<int32_t>(instruction.src1) - this->get<int32_t>(instruction.src2);
            this->set(instruction.dest, result);
            break;
        }
        case InstructionType::Mul:
        {
            const auto result = this->get<int32_t>(instruction.src1) * this->get<int32_t>(instruction.src2);
            this->set(instruction.dest, result);
            break;
        }
        case InstructionType::Div:
        {
            const auto result = this->get<int32_t>(instruction.src1) / this->get<int32_t>(instruction.src2);
            this->set(instruction.dest, result);
            break;
        }
        case InstructionType::Rem:
        {
            const auto result= this->get<int32_t>(instruction.src1) % this->get<int32_t>(instruction.src2);
            this->set(instruction.dest, result);
            break;
        }
        case InstructionType::Eq:
        {
            this->eq(instruction);
        }
        case InstructionType::EqNumber:
            this->eq(instruction);
            break;
        case InstructionType::EqBool:
            this->eq(instruction);
            break;
        case InstructionType::EqString:
            this->eq(instruction);
            break;
        case InstructionType::Neq:
            break;
        case InstructionType::Lt:
        {
            const auto result = this->get<int32_t>(instruction.src1) < this->get<int32_t>(instruction.src2);
            this->set(instruction.dest, result);
            break;
        }
        case InstructionType::Gt:
        {
            const auto result = this->get<int32_t>(instruction.src1) > this->get<int32_t>(instruction.src2);
            this->set(instruction.dest, result);
            break;
        }
        case InstructionType::Lte:
        {
            const auto result = this->get<int32_t>(instruction.src1) <= this->get<int32_t>(instruction.src2);
            this->set(instruction.dest, result);
            break;
        }
        case InstructionType::Gte:
        {
            const auto result = this->get<int32_t>(instruction.src1) >= this->get<int32_t>(instruction.src2);
            this->set(instruction.dest, result);
            break;
        }
        case InstructionType::And:
        {
            const auto result = this->get<bool>(instruction.src1) && this->get<bool>(instruction.src2);
            this->set(instruction.dest, result);
        }
        case InstructionType::Or:
        {
            const auto result = this->get<bool>(instruction.src1) || this->get<bool>(instruction.src2);
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
            this->print(instruction.src1);
            break;
        case InstructionType::PrintNumber:
            coutnl(this->get<int32_t>(instruction.src1));
            break;
        case InstructionType::PrintBool:
            coutnl(this->get<bool>(instruction.src1));
            break;
        case InstructionType::PrintString:
            coutnl(this->get<std::string>(instruction.src1));
            break;
        case InstructionType::Branch:
            this->program_counter = instruction.label;
            break;
        case InstructionType::BranchIf:
            if(this->get<bool>(instruction.src1)) this->program_counter = instruction.label;
            break;
    }
}