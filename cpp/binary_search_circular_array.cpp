// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::random_device;
using std::uniform_int_distribution;
using std::unordered_set;
using std::vector;

// @include
int search_smallest(const vector<int>& A)
{
    int left = 0;
    int right = static_cast<int>(A.size() - 1);
    while (left < right) {
        int mid = left + ((right - left) / 2);
        if (A[mid] > A[right]) {
            // Minimum must be in [mid + 1 : right].
            left = mid + 1;
        } else {  // A[mid] < A[right].
            // Minimum cannot be in [mid + 1 : right] so it must be in [left : mid].
            right = mid;
        }
    }
    // Loop ends when left == right.
    return left;
}
// @exclude

void simple_test()
{
    vector<int> A = {3, 1, 2};
    assert(1 == search_smallest(A));
    A = {0, 2, 4, 8};
    assert(0 == search_smallest(A));
    A[0] = 16;
    assert(1 == search_smallest(A));
    A = {2, 3, 4};
    assert(0 == search_smallest(A));
    A = {100, 101, 102, 2, 5};
    assert(3 == search_smallest(A));
    A = {10, 20, 30, 40, 5};
    assert(4 == search_smallest(A));
}

int main(int argc, char* argv[])
{
    simple_test();
    random_device rd;
    default_random_engine gen(rd());
    for (int times = 0; times < 1000; ++times) {
        int n;
        if (argc == 2) {
            n = atoi(argv[1]);
        } else {
            uniform_int_distribution<int> dis(1, 10000);
            n = dis(gen);
        }
        vector<int> A;
        unordered_set<int> table;
        for (size_t i = 0; i < n; ++i) {
            while (true) {
                uniform_int_distribution<int> dis(0, 100000);
                int x = dis(gen);
                if (table.emplace(x).second) {
                    A.emplace_back(x);
                    break;
                }
            }
        }
        sort(A.begin(), A.end());
        uniform_int_distribution<int> n_dis(0, n - 1);
        int shift = n_dis(gen);
        reverse(A.begin(), A.end());
        reverse(A.begin(), A.begin() + shift + 1);
        reverse(A.begin() + shift + 1, A.end());
        /*
           for (size_t i = 0; i < n; ++i) {
           cout << A[i] << ' ';
           }
           cout << "\n";
         */
        assert((shift + 1) % n == search_smallest(A));
    }
    return 0;
}
