
# targets

add_library(kbc
        tree.hpp
        parser.hpp
        parser.cpp
        compiler.hpp
        tests/__placeholder__.cpp
)
target_include_directories(kbc INTERFACE .)
set_build_flags(kbc)

add_executable(kbc_test tests/__placeholder__.cpp)
set_build_flags(kbc_test)


# libraries

target_link_libraries(kbc PRIVATE kbutils)
target_link_libraries(kbc PRIVATE fmt::fmt)
target_link_libraries(kbc PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(kbc_test PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)