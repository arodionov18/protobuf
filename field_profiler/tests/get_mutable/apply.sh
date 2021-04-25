cd build && make
cd ..
# protoc --plugin=protoc-gen-profiler-gen=./build/profiler-gen --cpp_out=. --profiler-gen_out=. caffe2.proto
protoc --plugin=protoc-gen-profiler-gen=./build/profiler-gen --cpp_out=./generated --profiler-gen_out=./generated test.proto