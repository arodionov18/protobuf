#!/bin/bash

configure() {
    mkdir -p generated
    mkdir -p build
    cd build
    cmake ../../../
    cd ..
}

generate() {
    cd build && make
    cd ..
    protoc --plugin=protoc-gen-profiler-gen=./build/profiler-gen --cpp_out=./generated --profiler-gen_out=./generated test.proto
}

generate_with_stripping() {
    cd build && make
    cd ..
    protoc --plugin=protoc-gen-profiler-gen=./build/profiler-gen --cpp_out=unused_field_stripping=true,access_info_map="stats.out":./generated --profiler-gen_out=unused_field_stripping=true,access_info_map="stats.out":./generated test.proto
}

compile_and_run() {
    clang++-10 main.cpp ./generated/test.pb.cc `pkg-config --cflags --libs protobuf` -I./generated -o main -g
    ./main
}

check_output() {
    failed=false
    result=`diff stats.out expected.txt`
    if [[ $? != 0 ]]; then
        echo "Test has failed. Diff:"
        echo $result
    else
        echo "Test has passed."
    fi
}

clean_up() {
    rm -rf generated main
}


configure

generate
compile_and_run
check_output
echo ''
echo 'File stat:'
stat main
echo ''

generate_with_stripping
compile_and_run
check_output
echo ''
echo 'Stripped file stat:'
stat main

clean_up