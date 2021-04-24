#include <iostream>
#include "test.pb.h"

using namespace std;

std::unordered_map<std::string, TrackerData> DynamicTracker::map_;

int main() {
    DynamicTracker tracker;
    test::ABC abc;
    abc.set_a(10);
    abc.set_b("xyi");
    std::cout << abc.a() << " " << abc.has_a() << " " << (abc.mutable_b() == nullptr) << endl;
    tracker.DumpStatistics("stats.out");
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}