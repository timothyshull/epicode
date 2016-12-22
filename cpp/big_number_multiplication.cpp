// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "execute_shell.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::max;
using std::ostream_iterator;
using std::random_device;
using std::string;
using std::stringstream;
using std::uniform_int_distribution;
using std::vector;

// @include
vector<int> multiply(vector<int> num1, vector<int> num2)
{
    const int sign = num1.front() < 0 ^ num2.front() < 0 ? -1 : 1;
    num1.front() = abs(num1.front()), num2.front() = abs(num2.front());

    vector<int> result(num1.size() + num2.size(), 0);
    for (int i = num1.size() - 1; i >= 0; --i) {
        for (int j = num2.size() - 1; j >= 0; --j) {
            result[i + j + 1] += num1[i] * num2[j];
            result[i + j] += result[i + j + 1] / 10;
            result[i + j + 1] %= 10;
        }
    }

    // Remove the leading zeroes.
    result = {
            find_if_not(begin(result), end(result), [](int a) { return a == 0; }),
            end(result)};
    if (result.empty()) {
        return {0};
    }
    result.front() *= sign;
    return result;
}
// @exclude

vector<int> rand_vector(int len)
{
    if (!len) { return {0}; }

    default_random_engine gen((random_device()) ());
    uniform_int_distribution<int> dis(1, 9);
    vector<int> ret;
    ret.emplace_back(dis(gen));
    --len;
    while (len--) {
        uniform_int_distribution<int> dis(0, 9);
        ret.emplace_back(dis(gen));
    }

    uniform_int_distribution<int> positive_or_negative(0, 1);
    if (positive_or_negative(gen)) {
        ret.front() *= -1;
    }
    return ret;
}

bool equal_vector(const vector<int>& A, const vector<int>& B)
{
    return equal(A.begin(), A.end(), B.begin(), B.end());
}

void simple_test()
{
    assert(equal_vector(multiply({0}, {-1, 0, 0, 0}), {0}));
    assert(equal_vector(multiply({0}, {1, 0, 0, 0}), {0}));
    assert(equal_vector(multiply({9}, {9}), {8, 1}));
    assert(equal_vector(multiply({9}, {9, 9, 9, 9}), {8, 9, 9, 9, 1}));
    assert(equal_vector(multiply({1, 3, 1, 4, 1, 2}, {-1, 3, 1, 3, 3, 3, 2}),
                        {-1, 7, 2, 5, 8, 7, 5, 8, 4, 7, 8, 4}));
    assert(equal_vector(multiply({7, 3}, {-3}), {-2, 1, 9}));
}

string VectorToString(const vector<int>& A)
{
    stringstream converter;
    copy(A.begin(), A.end(), ostream_iterator<int>(converter, ""));
    return converter.str();
}

int main(int argc, char* argv[])
{
    simple_test();
    for (int times = 0; times < 1000; ++times) {
        default_random_engine gen((random_device()) ());
        uniform_int_distribution<int> dis(0, 19);
        vector<int> num1 = rand_vector(dis(gen)), num2 = rand_vector(dis(gen));
        auto res = multiply(num1, num2);
        cout << VectorToString(num1) << " * " << VectorToString(num2) << " = "
             << VectorToString(res) << "\n";
        string command = "bash -c 'bc <<<" + VectorToString(num1) + "*" +
                         VectorToString(num2) + "'";
        string result = execute_shell(command);
        cout << "answer = " << result;
        assert(result.substr(0, result.size() - 1) == VectorToString(res));
    }
    return 0;
}
