#include <iostream>
#include "test.pb.h"

using namespace std;

std::unordered_map<std::string, TrackerData> DynamicTracker::map_;

void CallSetters(test::ABC& abc) {
    test::ABC::Nested nested;
    test::ABC::Nested::NestedInNested nested_in_nested;
    abc.clear_used();
    //abc.clear_unused();
    nested.clear_used();
    //nested.clear_unused();
    //nested_in_nested.clear_value();
}

void CallGetters(test::ABC& abc) {
    abc.has_used();
    test::ABC::Nested nested;
    nested.has_used();
}

int main() {
    DynamicTracker tracker;
    test::ABC abc;
    CallSetters(abc);
    CallGetters(abc);
    tracker.DumpStatistics("stats.out");
    auto res = tracker.DumpStatistics();
    for (const auto& elem: res) {
        cout << elem.first << " " << elem.second << endl;
    }
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}