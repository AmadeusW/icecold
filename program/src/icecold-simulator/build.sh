#!/bin/bash
CPP_FILES=$(find ../common -name "*.cpp" | tr '\n' ' ')
echo "Common files to be compiled:"
echo $CPP_FILES | tr ' ' '\n'
g++ -std=c++11 virtual_serial.cpp icecold-simulator.cpp $CPP_FILES -pthread -o simulator
