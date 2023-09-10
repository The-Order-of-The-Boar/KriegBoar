
# cmake config

cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE ./vcpkg/scripts/buildsystems/vcpkg.cmake CACHE PATH "vcpkg toolchain path")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# project config

set(CMAKE_CXX_FLAGS_DEBUG "" CACHE STRING "flags")
set(CMAKE_CXX_FLAGS_RELEASE  "" CACHE STRING "flags")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "" CACHE STRING "flags")
set(CMAKE_CXX_FLAGS_MINSIZEREL  "" CACHE STRING "flags")
set(CMAKE_CXX_STANDARD 20)

project(KriegBoar)


# kbc flags

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

            $<$<CONFIG:DEBUG>:-g>

            $<$<CONFIG:RELEASE>:-DNDEBUG>
            $<$<CONFIG:RELEASE>:-O3>
            $<$<CONFIG:RELEASE>:-flto>
            $<$<CONFIG:RELEASE>:-march=native>
    )

endfunction()


# libraries

find_package(fmt CONFIG REQUIRED)


# targets

add_subdirectory(src/kbc kbc)
add_subdirectory(src/kbvm kbvm)
