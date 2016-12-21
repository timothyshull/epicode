// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.
#include "test/test_options.h"
// @pg_ignore:1
#include "first_missing_positive.cpp"
// @pg_include:first-missing-positive.cc

void unit_test(TestSentry::Ptr& sentry, const char* description,
               const vector<int>& input, int expected)
{
    TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
    stream->RegisterInput(input);
    stream->RegisterExpectedOutput(expected);

    try {
        int result = FindFirstMissingPositive(input);
        stream->RegisterUserOutput(result, result == expected);
    }
    catch (...) {
        stream->RegisterUnhandledException();
    }
}

void directed_tests(const TestOptions& options)
{
    TestSentry::Ptr sentry = options.GetTestSentry(15, "Find the first missing positive entry");

    unit_test(sentry, "Trivial test", {}, 1);
    unit_test(sentry, "Negative numbers test", {-9, -16, -3, -1, -4}, 1);
    unit_test(sentry, "Positive numbers in ascending order test", {1, 2, 3, 4, 5}, 6);
    unit_test(sentry, "Positive numbers and zero in descending order test", {5, 4, 3, 2, 1, 0}, 6);
    unit_test(sentry, "Single missing number test", {5, -9, 3, 2, 1, 0}, 4);
    unit_test(sentry, "Multiple missing numbers test", {5, -9, 3, -8, 1, 8, 0}, 2);
}

int main(int argc, char* argv[])
{
    directed_tests(TestOptions(&cout));
    return 0;
}
