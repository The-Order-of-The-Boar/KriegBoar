
# target

add_library(kbvm
        vm.hpp
        tests/__placeholder__.cpp)
target_include_directories(kbvm INTERFACE .)
set_build_flags(kbvm)

add_executable(kbvm_test tests/__placeholder__.cpp)
set_build_flags(kbvm_test)


# libraries

target_link_libraries(kbvm PRIVATE kbutils)
target_link_libraries(kbvm PRIVATE fmt::fmt)
target_link_libraries(kbvm_test PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)