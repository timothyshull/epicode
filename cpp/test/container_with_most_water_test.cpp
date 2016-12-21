// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.
#include "test/test_options.h"
// @pg_ignore:1
#include "container_with_most_water.cpp"

// @pg_include:container-with-most-water.cc
void unit_test(TestSentry::Ptr& sentry, const char* description,
               const vector<int>& input, int expected)
{
    TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
    stream->RegisterInput(input);
    stream->RegisterExpectedOutput(expected);
    try {
        int result = GetMaxTrappedWater(input);
        stream->RegisterUserOutput(result, result == expected);
    }
    catch (...) {
        stream->RegisterUnhandledException();
    }
}

void directed_tests(const TestOptions& options)
{
    TestSentry::Ptr sentry = options.GetTestSentry(0, "Container with most water");

    unit_test(sentry, "Simple test #1", {1, 1}, 1);
    unit_test(sentry, "Simple test #2", {1, 1, 1, 1}, 3);
    unit_test(sentry, "Simple test #3", {10, 2, 1}, 2);
    unit_test(sentry, "Simple test #4", {1, 2, 10}, 2);
    unit_test(sentry, "Simple test #5", {10, 2, 10}, 20);
    unit_test(sentry, "Full test #1", {1, 4, 9, 16, 25, 16, 9, 3, 1}, 36);
    unit_test(sentry, "Full test #2", {1, 4, 9, 16, 25, 16, 9, 3, 1, 4, 9, 16, 25, 16, 9, 3, 1}, 200);
    unit_test(sentry, "Full test #3", {1, 4, 9, 16, 25, 16, 9, 3, 300, 1, 300, 4, 9, 16, 25, 16, 9, 3, 1}, 600);
    unit_test(sentry, "Full test #4", {1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1}, 48);
}

int main(int argc, char* argv[])
{
    directed_tests(TestOptions(&cout));
    return 0;
}
