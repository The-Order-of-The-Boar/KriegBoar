
#include "virtual_machine.h"

#include "../code/code.hpp"

int main()
{
    auto instructions = std::vector<Instruction>
    {
        Instruction{InstructionType::Print, "", "", "", 0}
    };

    KVirtualMachine virtual_machine{Code{instructions}};
}