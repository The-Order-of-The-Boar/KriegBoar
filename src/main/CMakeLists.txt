
# target

add_executable(kbmain main.cpp)
set_build_flags(kbmain)


# libraries

target_link_libraries(kbmain PRIVATE kbutils)
target_link_libraries(kbmain PRIVATE kbvm)
target_link_libraries(kbmain PRIVATE kbc)