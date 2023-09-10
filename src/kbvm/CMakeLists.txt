
# executable

add_executable(kbvm main.cpp)
set_build_flags(kbvm)


# libraries

target_link_libraries(kbvm PRIVATE fmt::fmt)
