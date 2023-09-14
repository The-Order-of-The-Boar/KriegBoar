#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>
#include <variant>

#include "../utils/assert.hpp"
#include "../code/code.hpp"

enum MemoryType
{
    Number,
    Bool,
    String
};

struct MemoryCell
{
   MemoryType type;
   std::variant<int32_t, bool, std::string> var;
};

template <class type>
void coutnl(const type& value)
{
    std::cout << value << std::endl;
}

class KVirtualMachine
{
private:
    size_t program_counter = 0;
    std::unordered_map<std::string, MemoryCell> memory{};

    template <class VarType>
    VarType get(const std::string& address) const
    {
        auto& var = this->memory.at(address).var;
        debug_assert(std::holds_alternative<VarType>(var), "Wrong type for get");
        return std::get<VarType>(var);
    }

    template <class VarType>
    void set(const std::string& address, const VarType value)
    {
        this->memory[address].var = value;
        this->memory[address].type = static_cast<MemoryType>(this->memory[address].var.index());
    }

    void add_number(const Instruction& instruction);
    void add_string(const Instruction& instruction);
    void add_number_string(const Instruction& instruction);
    void add_string_number(const Instruction& instruction);
    void add(const Instruction& instruction);

    void eq(const Instruction& instruction);

    void print(const std::string& address) const;

private:
    void execute_instruction(const Instruction& instruction);

public:
    KVirtualMachine(const Code& code);
};
