// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

// @include
int search_first_larger_of_k(const vector<int>& A, int k)
{
    int left = 0;
    int right = static_cast<int>(A.size() - 1);
    int result = -1;
    // [left : right] is the candidate set.
    while (left <= right) {
        int m = left + ((right - left) / 2);
        if (A[m] > k) {
            result = m;
            right = m - 1;  // Nothing to the right of mid can be solution.
        } else {  // A[m] <= k.
            left = m + 1;
        }
    }
    return result;
}
// @exclude

int CheckAns(const vector<int>& A, int k)
{
    for (int i = 0; i < A.size(); ++i) {
        if (A[i] > k) {
            return i;
        }
    }
    return -1;
}

static void simple_test()
{
    vector<int> A = {0, 1, 2, 3, 4, 5, 6, 7};
    int k = 4;
    assert(1 == search_first_larger_of_k(A, 0));
    assert(2 == search_first_larger_of_k(A, 1));
    assert(5 == search_first_larger_of_k(A, 4));
    assert(7 == search_first_larger_of_k(A, 6));
    assert(-1 == search_first_larger_of_k(A, 7));
    assert(0 == search_first_larger_of_k(A, -1));
    assert(0 == search_first_larger_of_k(A, numeric_limits<int>::min()));
    assert(-1 == search_first_larger_of_k(A, numeric_limits<int>::max()));
    A[0] = 1;
    assert(2 == search_first_larger_of_k(A, 1));
    A[5] = 4;
    A[6] = 4;
    assert(7 == search_first_larger_of_k(A, 4));
    A = {1, 1, 1, 1, 1, 2};
    assert(5 == search_first_larger_of_k(A, 1));
    assert(-1 == search_first_larger_of_k(A, 5));
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
            uniform_int_distribution<int> n_dis(1, 10000);
            n = n_dis(gen);
        }
        vector<int> A;
        for (int i = 0; i < n; ++i) {
            uniform_int_distribution<int> dis(0, n - 1);
            A.emplace_back(dis(gen));
        }
        sort(A.begin(), A.end());
        uniform_int_distribution<int> k_dis(0, n - 1);
        int k = k_dis(gen);
        int ans = search_first_larger_of_k(A, k);
        cout << "k = " << k << " locates at " << ans << "\n";
        if (ans != -1) {
            cout << "A[k] = " << A[ans] << "\n";
        }
        assert(ans == CheckAns(A, k));
    }
    return 0;
}
