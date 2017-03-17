// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <random>

// @include
int find_maximum_subarray(const std::vector<int>& a)
{
    auto min_sum = 0;
    auto sum = 0;
    auto max_sum = 0;
    for (auto i = 0; i < a.size(); ++i) {
        sum += a[i];
        if (sum < min_sum) { min_sum = sum; }
        if (sum - min_sum > max_sum) { max_sum = sum - min_sum; }
    }
    return max_sum;
}
// @exclude

template<typename Item_type>
std::vector<Item_type> rand_vector(std::size_t len)
{
    std::vector<Item_type> r(len);
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> dis{-1000, 1000};
    for (auto i = 0; i < len; ++i) { r[i] = dis(gen); }
    return r;
}

template<typename Item_type>
void check_max_sum(const std::vector<Item_type>& a, int max_sum)
{
    Item_type sum;
    for (auto i = 0; i < a.size(); ++i) {
        sum = 0;
        for (auto j = i; j < a.size(); ++j) {
            sum += a[j];
            assert(sum <= max_sum);
        }
    }
}

void small_test()
{
    std::vector<int> b{1};
    auto max_sum = find_maximum_subarray(b);
    check_max_sum(b, max_sum);
    b = {-5};
    max_sum = find_maximum_subarray(b);
    check_max_sum(b, max_sum);
    b = {0};
    max_sum = find_maximum_subarray(b);
    check_max_sum(b, max_sum);
    b = {0, 0};
    max_sum = find_maximum_subarray(b);
    check_max_sum(b, max_sum);
    b = {0, 0, 0};
    max_sum = find_maximum_subarray(b);
    check_max_sum(b, max_sum);
    b = {0, -5, 0};
    max_sum = find_maximum_subarray(b);
    check_max_sum(b, max_sum);
    b = {-2, -1};
    max_sum = find_maximum_subarray(b);
    check_max_sum(b, max_sum);
}

int main(int argc, char* argv[])
{
    small_test();
    std::random_device rd;
    std::default_random_engine gen{rd()};
    auto num_runs = 100; // 1000
    for (auto times = 0; times < num_runs; ++times) {
        std::vector<int> a;
        if (argc == 1) {
            std::uniform_int_distribution<std::size_t> dis{1, 10000};
            a = rand_vector<int>(dis(gen));
        } else if (argc == 2) {
            auto n = std::stoul(argv[1]);
            a = rand_vector<int>(n);
        } else {
            for (auto i = 1; i < argc; ++i) {
                a.push_back(std::stoi(argv[i]));
            }
        }
        auto max_sum = find_maximum_subarray(a);
        check_max_sum(a, max_sum);
    }
    return 0;
}
