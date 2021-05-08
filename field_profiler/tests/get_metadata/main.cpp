#include <iostream>
#include "test.pb.h"

using namespace std;

void CallSetters(test::ABC& abc, test::Meta& meta) {
    abc.clear_used();
    meta.clear_field();
}

void CallGetters(test::ABC& abc, test::Meta& meta) {
    abc.used();
    meta.field();
}

int main() {
    DynamicTracker tracker;
    test::ABC abc;
    test::Meta meta;
    CallSetters(abc, meta);
    CallGetters(abc, meta);
    
    meta.GetMetadata();
    tracker.DumpStatistics("stats.out");
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}