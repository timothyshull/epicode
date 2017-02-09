// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <iterator>

#include "test/test_options.h"
#include "anagrams.cpp"

void unit_test(TestSentry::Ptr& sentry, const char* description, const vector<string>& input, vector<vector<string>> expected)
{
    TestStream::Ptr stream = sentry->GetTestStream(TestType::NORMAL, description);
    stream->RegisterInput(input);

    for (auto& group : expected) { sort(group.begin(), group.end()); }

    sort(expected.begin(), expected.end());
    stream->RegisterExpectedOutput(expected);

    try {
        vector<vector<string>> result = find_anagrams(input);

        for (auto& group : result) { sort(group.begin(), group.end()); }

        sort(result.begin(), result.end());
        stream->RegisterUserOutput(result, result == expected);
    } catch (...) {
        stream->RegisterUnhandledException();
    }
}

void directed_tests(const TestOptions& options)
{
    TestSentry::Ptr sentry = options.GetTestSentry(10, "Anagrams");

    unit_test(sentry, "No anagrams test", {"elvis", "dormitory", "the eyes"}, {});
    unit_test(sentry, "Single anagram test", {"the eyes", "they see"}, {{"the eyes", "they see"}});
    unit_test(sentry, "Multiple anagrams test", {"aaa bb", "abb aa", "bb aaa", "aab", "aba", "baa", "aaa"}, {{"aaa bb", "abb aa", "bb aaa"}, {"aab",    "aba",    "baa"}});
    unit_test(sentry, "Latin anagrams test",
              {"quid est veritas ", "est vir qui adest",
               "ave maria, gratia plena, dominus tecum", "virgo serena, pia, munda et immaculata",
               "actus non facit reum nisi mens sit rea", "ad multos annos",
               "societas jesu", "vitiosa seces"},
              {{"quid est veritas ",                      "est vir qui adest"},
               {"ave maria, gratia plena, dominus tecum", "virgo serena, pia, munda et immaculata"}});
}

int main(int argc, char* argv[])
{
    directed_tests(TestOptions(&cout));
    return 0;
}
