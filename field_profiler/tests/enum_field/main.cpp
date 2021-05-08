#include <iostream>
#include "test.pb.h"

using namespace std;

void CallSetters(test::ABC& abc) {
    abc.clear_used();
    //abc.clear_unused();
}

void CallGetters(test::ABC& abc) {
    abc.used();
}

int main() {
    DynamicTracker tracker;
    test::ABC abc;
    CallSetters(abc);
    CallGetters(abc);
    tracker.DumpStatistics("stats.out");
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}