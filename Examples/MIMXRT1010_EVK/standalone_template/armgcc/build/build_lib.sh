#!/bin/sh

cmake -DIS_LIBRARY=1 -DCMAKE_TOOLCHAIN_FILE="../../../SDK_2.8.2_EVK-MIMXRT1010/tools/cmake_toolchain_files/armgcc.cmake" -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=debug  ..
make -j