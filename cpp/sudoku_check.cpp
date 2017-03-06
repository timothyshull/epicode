// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <cmath>
#include <deque>
#include <vector>

bool has_duplicate(const std::vector<std::vector<int>>&, std::size_t, std::size_t, std::size_t, std::size_t);

// @include
// Check if a partially filled matrix has any conflicts.
bool is_solvable_sudoku(const std::vector<std::vector<int>>& partial_assignment)
{
    // Check row constraints.
    for (std::size_t i = 0; i < partial_assignment.size(); ++i) {
        if (has_duplicate(partial_assignment, i, i + 1, 0, partial_assignment.size())) { return false; }
    }

    // Check column constraints.
    for (std::size_t j = 0; j < partial_assignment.size(); ++j) {
        if (has_duplicate(partial_assignment, 0, partial_assignment.size(), j, j + 1)) { return false; }
    }

    // Check region constraints.
    auto region_size = static_cast<std::size_t>(std::sqrt(partial_assignment.size())); // narrow_cast
    for (auto i2 = 0; i2 < region_size; ++i2) {
        for (auto j2 = 0; j2 < region_size; ++j2) {
            if (has_duplicate(
                    partial_assignment,
                    region_size * i2,
                    region_size * (i2 + 1),
                    region_size * j2,
                    region_size * (j2 + 1))
                    ) { return false; }
        }
    }
    return true;
}

// Return true if subarray partial_assignment[start_row : end_row -
// 1][start_col : end_col - 1] contains any duplicates in {1, 2, ...,
// partial_assignment.size()}; otherwise return false.
bool has_duplicate(
        const std::vector<std::vector<int>>& partial_assignment,
        std::size_t start_row,
        std::size_t end_row,
        std::size_t start_col,
        std::size_t end_col
)
{
    std::deque<bool> is_present(partial_assignment.size() + 1, false);
    for (auto i = start_row; i < end_row; ++i) {
        for (auto j = start_col; j < end_col; ++j) {
            if (partial_assignment[i][j] != 0 && is_present[partial_assignment[i][j]]) { return true; }
            is_present[partial_assignment[i][j]] = true;
        }
    }
    return false;
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
    assert(is_solvable_sudoku(a));
    // There are two 3s.
    a[8] = {3, 3, 8, 0, 0, 0, 4, 6, 0};
    assert(!is_solvable_sudoku(a));
    return 0;
}
