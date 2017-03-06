// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <cmath>
#include <deque>
#include <iostream>
#include <vector>

bool solve_sudoku(int, int, std::vector<std::vector<int>>&);

bool is_addable(const std::vector<std::vector<int>>&, int, int, int);

// @include
inline bool solve_sudoku(std::vector<std::vector<int>>& partial_assignment) { return solve_sudoku(0, 0, partial_assignment); }

bool solve_sudoku(int i, int j, std::vector<std::vector<int>>& partial_assignment)
{
    const static int empty_entry = 0;
    if (i == partial_assignment.size()) {
        i = 0; // starts a new row
        if (++j == partial_assignment[i].size()) { return true; } // Entire matrix has been filled without conflict
    }
    if ((partial_assignment)[i][j] != empty_entry) { return solve_sudoku(i + 1, j, partial_assignment); }
    for (auto val = 1; val <= partial_assignment.size(); ++val) {
        if (is_addable(partial_assignment, i, j, val)) {
            partial_assignment[i][j] = val;
            if (solve_sudoku(i + 1, j, partial_assignment)) { return true; }
        }
    }
    partial_assignment[i][j] = empty_entry;
    return false;
}

bool is_addable(const std::vector<std::vector<int>>& partial_assignment, int i, int j, int val)
{
    // Check row constraints
    for (auto v : partial_assignment) { if (v[j] == val) { return false; }}
    for (auto e : partial_assignment[i]) { if (e == val) { return false; }}

    // Check region constraints
    auto region_size = static_cast<int>(std::sqrt(partial_assignment.size())); // narrow_cast
    int i2 = i / region_size;
    int j2 = j / region_size;
    for (auto a = 0; a < region_size; ++a) {
        for (auto b = 0; b < region_size; ++b) {
            auto i3 = region_size * i2 + a;
            auto j3 = region_size * j2 + b;
            if (partial_assignment[i3][j3] == val) { return false; }
        }
    }
    return true;
}
// @exclude

int main(int argc, char* argv[])
{
    std::vector<std::vector<int>> a{
            {0, 2, 6, 0, 0, 0, 8, 1, 0},
            {3, 0, 0, 7, 0, 8, 0, 0, 6},
            {4, 0, 0, 0, 5, 0, 0, 0, 7},
            {0, 5, 0, 1, 0, 7, 0, 9, 0},
            {0, 0, 3, 9, 0, 5, 1, 0, 0},
            {0, 4, 0, 3, 0, 2, 0, 5, 0},
            {1, 0, 0, 0, 3, 0, 0, 0, 2},
            {5, 0, 0, 2, 0, 4, 0, 0, 9},
            {0, 3, 8, 0, 0, 0, 4, 6, 0}
    };
    assert(solve_sudoku(a));
    std::vector<std::vector<int>> expected{
            {7, 2, 6, 4, 9, 3, 8, 1, 5},
            {3, 1, 5, 7, 2, 8, 9, 4, 6},
            {4, 8, 9, 6, 5, 1, 2, 3, 7},
            {8, 5, 2, 1, 4, 7, 6, 9, 3},
            {6, 7, 3, 9, 8, 5, 1, 2, 4},
            {9, 4, 1, 3, 6, 2, 7, 5, 8},
            {1, 9, 4, 8, 3, 6, 5, 7, 2},
            {5, 6, 7, 2, 1, 4, 3, 8, 9},
            {2, 3, 8, 5, 7, 9, 4, 6, 1}
    };
    assert(a == expected);
    return 0;
}
