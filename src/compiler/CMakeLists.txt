
# targets

add_library(kbc
        tree.hpp
        parser.hpp
        parser.cpp
        compiler.hpp
)
target_include_directories(kbc INTERFACE .)
set_build_flags(kbc)

# libraries

target_link_libraries(kbc PRIVATE kbutils)
target_link_libraries(kbc PRIVATE fmt::fmt)
target_link_libraries(kbc PRIVATE nlohmann_json::nlohmann_json)
