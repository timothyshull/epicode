// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <random>
#include <string>

#include "can_string_be_palindrome_hash.h"
#include "can_string_be_palindrome_sorting.h"

using std::boolalpha;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::string;
using std::uniform_int_distribution;

string rand_string(int len)
{
    string ret;
    random_device rd;
    default_random_engine gen(rd());
    while (len--) {
        uniform_int_distribution<int> dis('a', 'z');
        ret += dis(gen);
    }
    return ret;
}

int main(int argc, char* argv[])
{
    random_device rd;
    default_random_engine gen(rd());
    for (int times = 0; times < 1000; ++times) {
        string s;
        if (argc == 2) {
            s = argv[1];
        } else {
            uniform_int_distribution<int> dis(1, 10);
            s = rand_string(dis(gen));
        }
        cout << s << "\n";
        assert(can_string_be_palindrome_hash::can_form_palindrome(s) ==
               can_string_be_a_palindrome_sorting::can_form_palindrome(&s));
    }
    return 0;
}
