// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>

void directed_combinations(int, int, int, std::vector<int>&, std::vector<std::vector<int>>&);

// @include
std::vector<std::vector<int>> combinations(int n, int k)
{
    std::vector<std::vector<int>> result;
    std::vector<int> t;
    directed_combinations(n, k, 1, t, result);
    return result;
}

void directed_combinations(
        int n,
        int k,
        int offset,
        std::vector<int>& partial_combination,
        std::vector<std::vector<int>>& result
)
{
    if (partial_combination.size() == k) {
        result.emplace_back(partial_combination);
        return;
    }

    // Generate remaining combinations over {offset, ..., n - 1} of size
    // num_remaining.
    const auto num_remaining = k - partial_combination.size();
    for (auto i = offset; i <= n && num_remaining <= n - i + 1; ++i) {
        partial_combination.emplace_back(i);
        directed_combinations(n, k, i + 1, partial_combination, result);
        partial_combination.pop_back();
    }
}
// @exclude

void small_test()
{
    auto result = combinations(4, 2);
    std::vector<std::vector<int>> expected{
            {1, 2},
            {1, 3},
            {1, 4},
            {2, 3},
            {2, 4},
            {3, 4}
    };
    assert(expected == result);
}

int main(int argc, char* argv[])
{
    small_test();
    std::random_device rd;
    std::default_random_engine gen{rd()};
    int n;
    int k;
    if (argc == 3) {
        n = std::stoi(argv[1]);
        k = std::stoi(argv[2]);
    } else {
        std::uniform_int_distribution<int> n_dis{1, 10};
        n = n_dis(gen);
        std::uniform_int_distribution<int> k_dis{0, n};
        k = k_dis(gen);
    }
    auto result = combinations(n, k);
    std::cout << "n = " << n << ", k = " << k << "\n";
    for (const auto& vec : result) {
        for (auto a : vec) { std::cout << a << " "; }
        std::cout << "\n";
    }
    return 0;
}
