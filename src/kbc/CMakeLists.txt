
# executable

add_executable(kbc main.cpp)
set_build_flags(kbc)


# libraries

target_link_libraries(kbc PRIVATE fmt::fmt)
