// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_INTERSECT_SORTED_ARRAYS3_H_
#define SOLUTIONS_INTERSECT_SORTED_ARRAYS3_H_

#include <vector>

using std::vector;

namespace Intersect_two_sorted_arrays3 {

// @include
    vector<int> intersect_two_sorted_arrays(const vector<int>& a, const vector<int>& b)
    {
        vector<int> intersection_a_b;
        int i = 0;
        int j = 0;
        while (i < a.size() && j < b.size()) {
            if (a[i] == b[j] && (i == 0 || a[i] != a[i - 1])) {
                intersection_a_b.emplace_back(a[i]);
                ++i;
                ++j;
            } else if (a[i] < b[j]) {
                ++i;
            } else {  // a[i] > b[j].
                ++j;
            }
        }
        return intersection_a_b;
    }
// @exclude

}  // namespace Intersect_two_sorted_arrays3

#endif  // SOLUTIONS_INTERSECT_SORTED_ARRAYS3_H_
