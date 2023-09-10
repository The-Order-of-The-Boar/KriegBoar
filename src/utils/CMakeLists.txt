
# target

add_library(utils
        source_location.hpp
        assert.cpp
        assert.hpp
)
target_include_directories(utils INTERFACE .)
set_build_flags(utils)

# libraries

target_link_libraries(utils PRIVATE fmt::fmt)
