#!/usr/bin/env bash
set -e


if [[ ! -e vcpkg ]]; then
    echo "uninitialized project"
    exit 1
fi

if (($# < 2)) || (($# > 2)); then
    echo "invalid number of parameters, usage: build.sh <build type> <target>"
    exit 1
fi

build_type=$1
target=$2

if [ "$build_type" != "Debug" ] && [ "$build_type" != "Release" ] && [ "$build_type" != "RelWithDebInfo" ]; then
    echo "invalid build mode"
    exit 1
fi

if [ "$target" != 'kbc' ] && [ "$target" != 'kbvm' ]; then
    echo "invalid target"
    exit 1
fi

cmake -B build -S . -DCMAKE_BUILD_TYPE="$build_type" -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build -j"$(getconf _NPROCESSORS_ONLN)" --target "$target"
