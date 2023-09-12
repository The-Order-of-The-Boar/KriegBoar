#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "../code/code.hpp"

union MemoryCell
{
    int int_var;
    bool bool_var;
    std::string string_var = "";

    ~MemoryCell(){};
};

class KVirtualMachine
{
private:
    size_t program_counter = 0;
    std::unordered_map<std::string, MemoryCell> memory{};

    int get_number(const std::string& address) const;
    bool get_bool(const std::string& address) const;
    const std::string& get_string(const std::string& address) const;

    void set(const std::string& address, const int);
    void set(const std::string& address, const bool);
    void set(const std::string& address, std::string);

private:
    void execute_instruction(const Instruction& instruction);

public:
    KVirtualMachine(const Code& code);
};