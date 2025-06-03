#!/bin/bash

# Clean build directory if it exists
if [ -d "build" ]; then
    echo "Cleaning build directory..."
    rm -rf build/*
else
    echo "Build directory not found. Creating a build directory..."
    mkdir build
fi

# Clean compiled extension files in mylib if it exists
echo "Cleaning compiled extensions in mylib..."
rm -f mylib/*.so mylib/*.pyd

pip install .