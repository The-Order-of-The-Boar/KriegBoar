
// builtin
#include <iostream>

// local
#include <vm.hpp>
#include <compiler.hpp>



bool const assert_exception = false;


int main() {

    std::cout << "KriegBoar main" << std::endl;
    func_vm();
    func_compiler();
}