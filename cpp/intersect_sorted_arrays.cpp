// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

#include "intersect_sorted_arrays1.h"
#include "intersect_sorted_arrays2.h"
#include "intersect_sorted_arrays3.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

void check_ans(const vector<int>& a, const vector<int>& b, const vector<int>& c)
{
    assert(equal(a.begin(), a.end(), b.begin(), b.end()));
    assert(equal(b.begin(), b.end(), c.begin(), c.end()));
}

int main(int argc, char* argv[])
{
    random_device rd;
    default_random_engine gen{rd()};
    for (int times = 0; times < 1000; ++times) {
        int n;
        int m;
        vector<int> a;
        vector<int> b;
        if (argc == 3) {
            n = atoi(argv[1]);
            m = atoi(argv[2]);
        } else {
            uniform_int_distribution<int> dis(1, 10000);
            n = dis(gen);
            m = dis(gen);
        }
        uniform_int_distribution<int> n_dis(0, n - 1);
        for (int i = 0; i < n; ++i) {
            a.emplace_back(n_dis(gen));
        }
        uniform_int_distribution<int> m_dis(0, m - 1);
        for (int j = 0; j < m; ++j) {
            b.emplace_back(m_dis(gen));
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        vector<int> res1 = Intersect_two_sorted_arrays1::intersect_two_sorted_arrays(a, b);
        vector<int> res2 = Intersect_two_sorted_arrays2::intersect_two_sorted_arrays(a, b);
        vector<int> res3 = Intersect_two_sorted_arrays3::intersect_two_sorted_arrays(a, b);
        check_ans(res1, res2, res3);
    }
    return 0;
}
