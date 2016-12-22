// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_TWOSUM_H_
#define SOLUTIONS_TWOSUM_H_

namespace Two_sum {

#include <vector>

    using std::vector;

    // @include
    bool has_two_sum(const vector<int>& A, int t)
    {
        int i = 0, j = A.size() - 1;
        while (i <= j) {
            if (A[i] + A[j] == t) {
                return true;
            } else if (A[i] + A[j] < t) {
                ++i;
            } else {  // A[i] + A[j] > t.
                --j;
            }
        }
        return false;
    }
    // @exclude

}  // namespace Two_sum

#endif  // SOLUTIONS_TWOSUM_H_
