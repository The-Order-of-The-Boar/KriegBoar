
# target

add_library(code
        code.hpp
)
target_include_directories(code INTERFACE .)
set_build_flags(code)

# libraries

target_link_libraries(code PRIVATE fmt::fmt)
