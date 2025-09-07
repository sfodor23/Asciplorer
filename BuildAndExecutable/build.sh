#!/bin/bash
# filepath: /home/sfodor/Documents/RealNationalConquest/MainProgram/build.sh

echo "Building Asciplorer..."

# Clean old build
rm -f Asciplorer

# Compile
g++ -std=c++17 -Wall -O2 \
    -o Asciplorer \
    ../MainProgram/Asciplorer.cpp \
    ../ProgramMethods/MiscMethods.cpp \
    ../ProgramMethods/ArrayGenerationMethods.cpp \
    ../ProgramMethods/InputMethods.cpp \
    ../ProgramMethods/KnownLocationsMethods.cpp \
    ../ProgramMethods/PlayerMethods.cpp \
    ../ProgramMethods/StatisticTrackingMethods.cpp \
    ../RealTimeStatistics/RealTimeStatistics.cpp

# Check if it worked
if [ $? -eq 0 ]; then
    echo "✓ Build successful!"
    echo "Run with: ./Asciplorer"
else
    echo "✗ Build failed!"
    echo "Verify Integrity of Program Files"
fi