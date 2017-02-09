// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_INTERSECT_SORTED_ARRAYS1_H_
#define SOLUTIONS_INTERSECT_SORTED_ARRAYS1_H_

#include <vector>

using std::vector;

namespace Intersect_two_sorted_arrays1 {

// @include
    vector<int> intersect_two_sorted_arrays(const vector<int>& a, const vector<int>& b)
    {
        vector<int> insersection_a_b;
        for (int i = 0; i < a.size(); ++i) {
            if (i == 0 || a[i] != a[i - 1]) {
                for (int c : b) {
                    if (a[i] == c) {
                        insersection_a_b.emplace_back(a[i]);
                        break;
                    }
                }
            }
        }
        return insersection_a_b;
    }
// @exclude

}  // namespace Intersect_two_sorted_arrays1

#endif  // SOLUTIONS_INTERSECT_SORTED_ARRAYS1_H_
