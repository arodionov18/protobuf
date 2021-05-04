#!/bin/bash

clang++-10 main.cpp ./generated/test.pb.cc `pkg-config --cflags --libs protobuf` -I./generated -o main -g
./main

failed=false
result=`diff stats.out expected.txt`
if [[ $? != 0 ]]; then
    echo "Test has failed. Diff:"
    echo $result
else
    echo "Test has passed."
fi

#rm stats.out main
