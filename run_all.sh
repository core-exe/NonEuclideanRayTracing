#!/usr/bin/env bash

# If project not ready, generate cmake file.
if [[ ! -d build ]]; then
    echo "good"
else
    rm -rf build
fi
mkdir -p build
cd build
cmake ..
make -j CC='usr/bin/gcc-9'
cd ..

# Run all testcases. 
# You can comment some lines to disable the run of specific examples.