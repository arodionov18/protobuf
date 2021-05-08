#include <iostream>
#include <thread>
#include "test.pb.h"

using namespace std;

void CallGettersFirst(test::ABC& abc) {
    abc.a1();
    abc.a2();
    abc.a3();
    abc.a4();
}

void CallGettersSecond(test::ABC& abc) {
    abc.b1();
    abc.b2();
    abc.b3();
    abc.b4();
}

void CallGettersThird(test::ABC& abc) {
    abc.c1();
    abc.c2();
    abc.c3();
    abc.c4();
}

void CallGettersFourth(test::ABC& abc) {
    abc.d1();
    abc.d2();
    abc.d3();
    abc.d4();
}

int main() {
    DynamicTracker tracker;
    test::ABC abc;

    thread t1(CallGettersFirst, ref(abc));
    thread t2(CallGettersSecond, ref(abc));
    thread t3(CallGettersThird, ref(abc));
    thread t4(CallGettersFourth, ref(abc));

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    tracker.DumpStatistics("stats.out");
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}