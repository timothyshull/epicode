// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.
#include "test/test_options.h"
// @pg_ignore:1
#include "Gassing_up.cpp"
// @pg_include:Gassing_up.cc

void unit_test(TestSentry::Ptr& sentry, const char* description,
               const vector<int>& gallons, vector<int> distances_measured_in_gallons,
               size_t expected)
{
    for (auto& x : distances_measured_in_gallons) { //Convert distance to miles
        x *= kMPG;
    }

    TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
    stream->GetInputWriter()->
            WritePair("MPG", kMPG).
            WritePair("Distances", distances_measured_in_gallons).
            WritePair("Gallons", gallons);
    stream->RegisterExpectedOutput(expected);
    try {
        size_t result = FindAmpleCity(gallons, distances_measured_in_gallons);
        stream->RegisterUserOutput(result, result == expected);
    } catch (...) {
        stream->RegisterUnhandledException();
    }
}

void directed_tests(const TestOptions& options)
{
    TestSentry::Ptr sentry = options.GetTestSentry(12, "Gassing up");

    unit_test(sentry, "Trivial test", {0}, {0}, 0);
    unit_test(sentry, "Small test", {7, 2, 20}, {13, 5, 7}, 2);
    unit_test(sentry, "Medium test",
              {0, 18, 13, 16, 7, 8, 4, 17}, {2, 28, 1, 15, 4, 18, 8, 7}, 2);
    unit_test(sentry, "Huge test",
              {20, 15, 15, 15, 35, 25, 30, 15, 65, 45, 10, 45, 25},
              {15, 20, 50, 15, 15, 30, 20, 55, 20, 50, 10, 15, 15}, 8);
    unit_test(sentry, "The largest amount of gas test",
              {200, 2, 2, 2, 10, 10}, {100, 40, 40, 40, 2, 2}, 4);
    unit_test(sentry, "The shortest segment test",
              {30, 90, 30, 2, 10, 10}, {40, 30, 20, 40, 2, 40}, 1);
}

int main(int argc, char* argv[])
{
    directed_tests(TestOptions(&cout));
    return 0;
}
