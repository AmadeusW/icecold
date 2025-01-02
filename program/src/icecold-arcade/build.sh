#!/bin/bash
CPP_FILES=$(find ../common -name "*.cpp" | tr '\n' ';')
echo "Common files to be compiled:"
echo $CPP_FILES | tr ';' '\n'
arduino-cli compile -v --fqbn arduino:avr:mega \
    --build-property "-std=gnu++11" \
    --build-property "build.extra_flags=-I../common" \
    --build-property "build.extra_source_files=$CPP_FILES" 