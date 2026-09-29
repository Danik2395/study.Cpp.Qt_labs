#!/bin/bash
TEST_NAME="test_classes"
clang ${TEST_NAME}.cpp -std=c++20 -lstdc++ -o ${TEST_NAME}.out && ./${TEST_NAME}.out
