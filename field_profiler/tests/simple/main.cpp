#include <iostream>
#include "test.pb.h"

using namespace std;

std::unordered_map<std::string, TrackerData> DynamicTracker::map_;

int main() {
    DynamicTracker tracker;
    test::ABC abc;
    abc.set_a(10);
    abc.set_b("string");
    std::cout << abc.a() << " " << (abc.mutable_b() == nullptr) << endl;
    tracker.DumpStatistics("stats.out");
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}