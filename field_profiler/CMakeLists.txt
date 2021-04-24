cmake_minimum_required(VERSION 3.10)
find_package(Protobuf REQUIRED)
MESSAGE("${Protobuf_FOUND}")
MESSAGE("${Protobuf_VERSION}")
MESSAGE("${Protobuf_LIBRARIES}")
find_library(PTHREAD_LIBRARY pthread)
find_library(PROTOBUF protobuf)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")


add_executable(profiler-gen
    main.cpp
    insert_profiler.cpp)

target_link_libraries(profiler-gen ${PTHREAD_LIBRARY} ${PROTOBUF} ${PROTOBUF_LIBRARIES} protoc)
