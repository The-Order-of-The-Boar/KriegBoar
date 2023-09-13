
# target

add_library(kbutils
        source_location.hpp
        assert.cpp
        assert.hpp
)
target_include_directories(kbutils INTERFACE .)
set_build_flags(kbutils)

add_executable(kbutils_test
        tests/assert.cpp)
set_build_flags(kbutils_test)

# libraries

target_link_libraries(kbutils PRIVATE fmt::fmt)

target_link_libraries(kbutils_test PRIVATE kbutils)
target_link_libraries(kbutils_test PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)