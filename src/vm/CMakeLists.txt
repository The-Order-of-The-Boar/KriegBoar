
# target

add_library(kbvm
        vm.hpp
)
target_include_directories(kbvm INTERFACE .)
set_build_flags(kbvm)


# libraries

target_link_libraries(kbvm PRIVATE kbutils)
target_link_libraries(kbvm PRIVATE fmt::fmt)
