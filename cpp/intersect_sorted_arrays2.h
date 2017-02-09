// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_INTERSECT_SORTED_ARRAYS2_H_
#define SOLUTIONS_INTERSECT_SORTED_ARRAYS2_H_

#include <algorithm>
#include <vector>

using std::vector;

namespace Intersect_two_sorted_arrays2 {

// @include
    vector<int> intersect_two_sorted_arrays(const vector<int>& a, const vector<int>& b)
    {
        vector<int> intersection_a_b;
        for (int i = 0; i < a.size(); ++i) {
            if ((i == 0 || a[i] != a[i - 1]) && std::binary_search(b.cbegin(), b.cend(), a[i])) {
                intersection_a_b.emplace_back(a[i]);
            }
        }
        return intersection_a_b;
    }
// @exclude

}  // namespace Intersect_two_sorted_arrays2

#endif  // SOLUTIONS_INTERSECT_SORTED_ARRAYS2_H_
