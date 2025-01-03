#!/bin/bash
CPP_FILES=$(find ../common -name "*.cpp" | tr '\n' ' ')
echo "Common files to be compiled:"
echo $CPP_FILES | tr ' ' '\n'
g++ -std=c++11 icecold-simulator.cpp simulatorModule.cpp $CPP_FILES -pthread -o simulator
