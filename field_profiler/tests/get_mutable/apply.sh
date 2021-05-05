cd build && make
cd ..
# protoc --plugin=protoc-gen-profiler-gen=./build/profiler-gen --cpp_out=. --profiler-gen_out=. caffe2.proto
protoc --plugin=protoc-gen-profiler-gen=./build/profiler-gen --cpp_out=./generated --profiler-gen_out=./generated test.proto
#protoc --plugin=protoc-gen-profiler-gen=./build/profiler-gen --cpp_out=unused_field_stripping=true,access_info_map="stats.out":./generated --profiler-gen_out=unused_field_stripping=true:./generated test.proto
