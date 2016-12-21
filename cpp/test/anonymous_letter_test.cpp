// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.
#include "test/test_options.h"
// @pg_ignore:1
#include "anonymous_letter.cpp"

// @pg_include:Anonymous_letter.cc
void unit_test(TestSentry::Ptr& sentry, const char* description,
               const string& letter, const string& magazine,
               bool expected)
{
    TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
    stream->GetInputWriter()->
            WritePair("magazine", magazine).
            WritePair("letter", letter);
    stream->RegisterExpectedOutput(expected);
    try {
        bool result = is_letter_constructible_from_magazine(letter, magazine);
        stream->RegisterUserOutput(result, result == expected);
    } catch (...) {
        stream->RegisterUnhandledException();
    }
}

void directed_tests(const TestOptions& options)
{
    TestSentry::Ptr sentry = options.GetTestSentry(0, "Anonymous letter");

    unit_test(sentry, "No duplicate characters test #1", "123", "456", false);
    unit_test(sentry, "No duplicate characters test #2", "123", "123", true);
    unit_test(sentry, "Simple test #1", "123", "12222222", false);
    unit_test(sentry, "Simple test #2", "123", "1123", true);
    unit_test(sentry, "Simple test #3", "12323", "123", false);
    unit_test(sentry, "Simple test #4", "aa", "aa", true);
    unit_test(sentry, "Simple test #5", "aa", "aaa", true);
    unit_test(sentry, "Empty input test #1", "a", "", false);
    unit_test(sentry, "Empty input test #2", "", "123", true);
    unit_test(sentry, "Empty input test #3", "", "", true);
    unit_test(sentry, "Full test", "GATTACA", "A AD FS GA T ACA TTT", true);

}

int main(int argc, char* argv[])
{
    directed_tests(TestOptions(&cout));
    return 0;
}
