
# target

add_executable(kbtests assert.cpp)
set_build_flags(kbtests)


# libraries

target_link_libraries(kbtests PRIVATE kbc kbvm kbcode kbutils)
target_link_libraries(kbtests PRIVATE Catch2::Catch2 Catch2::Catch2WithMain)
