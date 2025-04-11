
# target

add_library(kbcode
        code.hpp
)
target_include_directories(kbcode INTERFACE .)
set_build_flags(kbcode)

# libraries

target_link_libraries(kbcode PRIVATE fmt::fmt)
