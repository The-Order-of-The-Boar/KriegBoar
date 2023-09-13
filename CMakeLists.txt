
# cmake config

cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE ./vcpkg/scripts/buildsystems/vcpkg.cmake CACHE PATH "vcpkg toolchain path")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# project config

project(KriegBoar)

set(CMAKE_CXX_FLAGS_DEBUG "" CACHE STRING "flags" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "" CACHE STRING "flags" FORCE)
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "" CACHE STRING "flags" FORCE)
set(CMAKE_CXX_STANDARD 20)

# compiler flags

if ((NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") AND (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))
    message(FATAL "unsupported compiler")
endif()

function(set_build_flags executable)

    target_link_libraries(${executable} PRIVATE

            $<$<CONFIG:RELEASE>:-flto>
            $<$<CONFIG:DEBUG>:-fsanitize=address>
            $<$<CONFIG:DEBUG>:-fsanitize=undefined>
    )

    target_compile_options(${executable} PRIVATE

            -std=c++20
            -pedantic -Wall -Wextra
            -Werror=switch
            -fdiagnostics-color=always

            $<$<CONFIG:DEBUG,RELWITHDEBINFO>:-g>
            $<$<CONFIG:RELEASE>:-DNDEBUG>

            $<$<CONFIG:RELEASE,RELWITHDEBINFO>:-O3>
            $<$<CONFIG:RELEASE,RELWITHDEBINFO>:-flto>
            $<$<CONFIG:RELEASE,RELWITHDEBINFO>:-march=native>
    )

endfunction()


# libraries

find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)


# targets

add_subdirectory(src/utils kbutils)
add_subdirectory(src/compiler kbc)
add_subdirectory(src/vm kbvm)
add_subdirectory(src/code kbcode)
add_subdirectory(src/main kbmain)
add_subdirectory(src/tests kbtests)
