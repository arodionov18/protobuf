#include <memory>

#include "insert_profiler.h"

#include <google/protobuf/compiler/plugin.h>

int main(int argc, char *argv[]) {
    ProfilerGenerator generator;

    return google::protobuf::compiler::PluginMain(argc, argv, &generator);
}