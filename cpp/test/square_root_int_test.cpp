// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.
#include "test/test_options.h"
// @pg_ignore:1
#include "square_root_int.cpp"
// @pg_include:square-root-int.cc

void UnitTest(TestSentry::Ptr& sentry, const char* description,
              int input, int expected)
{
    TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
    stream->RegisterInput(input);
    stream->RegisterExpectedOutput(expected);
    try {
        int result = SquareRoot(input);
        stream->RegisterUserOutput(result, result == expected);
    }
    catch (...) {
        stream->RegisterUnhandledException();
    }
}

void directed_tests(const TestOptions& options)
{
    TestSentry::Ptr sentry = options.GetTestSentry(9, "Integer Square Root");

    UnitTest(sentry, "Zero value test", 0, 0);
    UnitTest(sentry, "K = 1 test", 1, 1);
    UnitTest(sentry, "K = 2 test", 2, 1);
    UnitTest(sentry, "K = 3 test", 3, 1);
    UnitTest(sentry, "K = 4 test", 4, 2);
    UnitTest(sentry, "K = 8 test", 8, 2);
    UnitTest(sentry, "K = 9 test", 9, 3);
    UnitTest(sentry, "K = 64 test", 64, 8);
    UnitTest(sentry, "K = 121 test", 121, 11);
    UnitTest(sentry, "K = 300 test", 300, 17);
    /*unit_test(sentry, "Max int test", numeric_limits<int32_t>::max(), 46340);*/
}

int main(int argc, char* argv[])
{
    directed_tests(TestOptions(&cout));
    return 0;
}
