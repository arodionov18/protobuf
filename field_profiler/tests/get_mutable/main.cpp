#include <iostream>
#include "test.pb.h"

using namespace std;

int main() {
    DynamicTracker tracker;
    test::ABC abc;
    abc.add_a_index(12);
    abc.set_b("string");
    abc.set_c("bytes");
    test::ABC::Nested nested;
    nested.set_value(true);
    nested.value();
    //abc.set_allocated_d(&nested);
    //std::cout << abc.a() << " " << abc.has_a() << " " << (abc.mutable_b() == nullptr) << endl;
    abc.has_d();
    abc.a();
    abc.a_index(0);
    abc.mutable_b();
    abc.mutable_c();
    abc.mutable_d();
    tracker.DumpStatistics("stats.out");
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}