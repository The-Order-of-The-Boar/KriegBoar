#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

#include "../code/code.hpp"

enum MemoryType
{
    Number,
    Bool,
    String
};

union MemoryVar
{
    int number_var;
    bool bool_var;
    std::string string_var = "";

    ~MemoryVar(){};
};

struct MemoryCell
{
   MemoryType type;
   MemoryVar var;
};

class KVirtualMachine
{
private:
    size_t program_counter = 0;
    std::unordered_map<std::string, MemoryCell> memory{};

    int get_number(const std::string& address) const;
    bool get_bool(const std::string& address) const;
    const std::string& get_string(const std::string& address) const;

    void set(const std::string& address, const int value);
    void set(const std::string& address, const bool value);
    void set(const std::string& address, std::string value);

    void add(const Instruction& instruction);
    void add_number(const Instruction& instruction);
    void add_string(const Instruction& instruction);
    void add_number_string(const Instruction& instruction);
    void add_string_number(const Instruction& instruction);

private:
    void execute_instruction(const Instruction& instruction);

public:
    KVirtualMachine(const Code& code);
};

template <class type>
void coutnl(const type& value)
{
    std::cout << value << std::endl;
}