
# target

add_library(utils __placeholder__.cpp)
target_include_directories(utils INTERFACE .)
set_build_flags(utils)

# libraries

target_link_libraries(utils PRIVATE fmt::fmt)
