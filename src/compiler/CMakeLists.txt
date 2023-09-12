
# target

add_executable(kbc main.cpp
        tree.hpp
)
set_build_flags(kbc)


# libraries

target_link_libraries(kbc PRIVATE kbutils)
target_link_libraries(kbc PRIVATE fmt::fmt)
target_link_libraries(kbc PRIVATE nlohmann_json::nlohmann_json)