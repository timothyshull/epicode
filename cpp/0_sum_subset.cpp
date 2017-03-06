// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>

// @include
std::vector<int> find_0_sum_subset(const std::vector<int>& v)
{
    std::vector<int> prefix_sum(v);
    for (int i{0}; i < prefix_sum.size(); ++i) {
        prefix_sum[i] += i > 0 ? prefix_sum[i - 1] : 0;
        prefix_sum[i] %= v.size();
    }

    std::vector<int> table(v.size(), -1);
    for (int i{0}; i < v.size(); ++i) {
        if (prefix_sum[i] == 0) {
            std::vector<int> ans(static_cast<std::vector<int>::size_type>(i + 1));
            std::iota(ans.begin(), ans.end(), 0);
            return ans;
        } else if (table[prefix_sum[i]] != -1) {
            std::vector<int> ans(static_cast<std::vector<int>::size_type>(i - table[prefix_sum[i]]));
            std::iota(ans.begin(), ans.end(), table[prefix_sum[i]] + 1);
            return ans;
        }
        table[prefix_sum[i]] = i;
    }
    // @exclude
    return {};  // it should not happen
    // @include
}
// @exclude

void check_ans(const std::vector<int>& A, const std::vector<int>& ans)
{
    std::size_t sum{0};
    for (int a : ans) { sum = (sum + A[a]) % A.size(); }
    assert(sum == 0);
}

int main(int argc, char* argv[])
{
    std::random_device rd;
    std::default_random_engine gen{rd()};
    for (int times{0}; times < 1000; ++times) {
        std::size_t n;
        std::vector<int> v;
        if (argc == 2) {
            n = std::stoul(argv[1]);
            v.resize(n);
            std::uniform_int_distribution<int> dis{0, 9999};
            for (int i{0}; i < n; ++i) { v[i] = dis(gen); }
        } else if (argc > 2) {
            for (int i = 1; i < argc; ++i) {
                v.emplace_back(atoi(argv[i]));
            }
        } else {
            std::uniform_int_distribution<std::size_t> n_dis{1, 100};
            n = n_dis(gen);
            v.resize(n);
            std::uniform_int_distribution<int> dis{0, 9999};
            for (int i{0}; i < n; ++i) { v[i] = dis(gen); }
        }
        std::vector<int> ans{find_0_sum_subset(v)};
        check_ans(v, ans);
    }
    return 0;
}
