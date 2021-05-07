#include <iostream>
#include "test.pb.h"

using namespace std;

std::unordered_map<std::string, TrackerData> DynamicTracker::map_;

void CallSetters(test::ABC& abc) {
    abc.clear_used();
    abc.clear_used();
    // abc.clear_unused();
    // abc.clear_unused();
}

void CallGetters(test::ABC& abc) {
    abc.a();
    abc.has_b();
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