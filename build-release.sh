#!/bin/bash
set -e

echo "Cleaning build directory..."
rm -rf build
mkdir build && cd build

echo "Detecting generator type..."

# Run cmake with no generator first to extract info
cmake -DCMAKE_INSTALL_PREFIX=.. .. -LA > /dev/null

GENERATOR=$(grep CMAKE_GENERATOR:INTERNAL CMakeCache.txt | cut -d= -f2)
echo "Generator: $GENERATOR"

echo "Building in Release mode..."

if [[ "$GENERATOR" == *"Visual Studio"* || "$GENERATOR" == *"Xcode"* ]]; then
    # Multi-config generators: must specify --config
    cmake --build . --config Release
    cmake --install . --config Release
else
    # Single-config generators like Ninja or Unix Makefiles
    rm -rf *  # Clear and reconfigure with Release mode
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=.. ..
    cmake --build .
    cmake --install .
fi

echo "Build and install complete."
