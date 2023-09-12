#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "../code/code.hpp"

union MemoryCell
{
    int int_var;
    bool bool_var;
    std::unique_ptr<std::string> string_var;

    ~MemoryCell(){};
};

class KVirtualMachine
{
private:
    size_t program_counter = 0;
    std::unordered_map<std::string, MemoryCell> memory{};

private:
    void execute_instruction(const Instruction& instruction);

public:
    KVirtualMachine(const Code& code);
};