#include <iostream>
#include "test.pb.h"

using namespace std;

void CallSetters(test::ABC& abc) {
    abc.clear_used();
}

void CallGetters(test::ABC& abc) {
    abc.used();
}

int main() {
    DynamicTracker tracker;
    test::ABC abc;
    CallSetters(abc);
    CallGetters(abc);
    string result;

    abc.SerializeToString(&result);
    
    tracker.DumpStatistics("stats.out");
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}