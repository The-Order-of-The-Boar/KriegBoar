
# target

add_library(kbutils
        source_location.hpp
        assert.cpp
        assert.hpp
)
target_include_directories(kbutils INTERFACE .)
set_build_flags(kbutils)

# libraries

target_link_libraries(kbutils PRIVATE fmt::fmt)
