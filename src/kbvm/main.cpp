
#include <array>
#include <iostream>
#include <vector>


enum class InstructionType {
    Set,
    Add,
    Mul,
    Print
};

struct Instruction {
    InstructionType type;
    size_t a = 0;
    size_t b = 0;
    size_t dest = 0;
};

void run(std::vector<Instruction> const& code)
{
    std::array<int32_t, 10> mem{0};

    for (auto inst: code) {
        switch (inst.type) {

            case InstructionType::Add:
                mem[inst.dest] = mem[inst.a] + mem[inst.b];
                break;

            case InstructionType::Mul:
                mem[inst.dest] = mem[inst.a] * mem[inst.b];
                break;

            case InstructionType::Print:
                std::cout << mem[inst.dest] << std::endl;
                break;

            case InstructionType::Set:
                mem[inst.dest] = inst.a;
                break;
        }
    }
}

int main()
{
    auto code = std::vector<Instruction>{
        Instruction{.type = InstructionType::Set,   .a = 10, .b = 0, .dest = 0},
        Instruction{.type = InstructionType::Print, .a = 0,  .b = 0, .dest = 0},
        Instruction{.type = InstructionType::Set,   .a = 20, .b = 0, .dest = 1},
        Instruction{.type = InstructionType::Print, .a = 0,  .b = 0, .dest = 1},
        Instruction{.type = InstructionType::Add,   .a = 0,  .b = 1, .dest = 6},
        Instruction{.type = InstructionType::Print, .a = 0,  .b = 0, .dest = 6}
    };

    run(code);
}