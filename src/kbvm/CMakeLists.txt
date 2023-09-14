
# target

add_executable(kbvm main.cpp
        virtual_machine.cpp
        ../utils/assert.cpp
)
set_build_flags(kbvm)


# libraries

target_link_libraries(kbvm PRIVATE utils)
target_link_libraries(kbvm PRIVATE fmt::fmt)
