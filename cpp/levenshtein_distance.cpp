// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>

int compute_distance_between_prefixes(
        const std::string& a,
        int a_idx,
        const std::string& b,
        int b_idx,
        std::vector<std::vector<int>>& distance_between_prefixes);

int levenshtein_distance(const std::string& a, const std::string& b)
{
    std::vector<std::vector<int>> distance_between_prefixes(a.size(), std::vector<int>(b.size(), -1));
    // narrow_cast
    return compute_distance_between_prefixes(a, static_cast<int>(a.size() - 1), b, static_cast<int>(b.size() - 1), distance_between_prefixes);
}

int compute_distance_between_prefixes(
        const std::string& a,
        int a_idx,
        const std::string& b,
        int b_idx,
        std::vector<std::vector<int>>&& distance_between_prefixes)
{
    // std::vector<std::vector<int>>& distance_between_prefixes = *distance_between_prefixes_ptr;
    if (a_idx < 0) {
        // A is empty so add all of B's characters.
        return b_idx + 1;
    } else if (b_idx < 0) {
        // B is empty so delete all of A's characters.
        return a_idx + 1;
    }
    if (distance_between_prefixes[a_idx][b_idx] == -1) {
        if (a[a_idx] == b[b_idx]) {
            distance_between_prefixes[a_idx][b_idx] = compute_distance_between_prefixes(
                    a,
                    a_idx - 1,
                    b,
                    b_idx - 1,
                    distance_between_prefixes);
        } else {
            int substitute_last{compute_distance_between_prefixes(a, a_idx - 1, b, b_idx - 1, distance_between_prefixes)};
            int add_last{compute_distance_between_prefixes(a, a_idx - 1, b, b_idx, distance_between_prefixes)};
            int delete_last{compute_distance_between_prefixes(a, a_idx, b, b_idx - 1, distance_between_prefixes)};
            distance_between_prefixes[a_idx][b_idx] = 1 + std::min({substitute_last, add_last, delete_last});
        }
    }
    return distance_between_prefixes[a_idx][b_idx];
}
// @exclude

int check_answer(std::string a, std::string b)
{
    // Try to reduce the space usage.
    if (a.size() < b.size()) {
        std::swap(a, b);
    }

    std::vector<int> d(b.size() + 1);
    // Initialization.
    std::iota(d.begin(), d.end(), 0);

    for (int i = 1; i <= a.size(); ++i) {
        int pre_i_1_j_1{d[0]};  // Stores the value of D[i - 1][j - 1].
        d[0] = i;
        for (int j = 1; j <= b.size(); ++j) {
            int pre_i_1_j{d[j]};  // Stores the value of D[i -1][j].
            d[j] = a[i - 1] == b[j - 1] ? pre_i_1_j_1 : 1 + std::min({pre_i_1_j_1, d[j - 1], d[j]});
            // Previous D[i - 1][j] will become the next D[i - 1][j - 1].
            pre_i_1_j_1 = pre_i_1_j;
        }
    }
    return d.back();
}

std::string rand_string(int len)
{
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<int> dis{'a', 'z'};
    std::string ret;
    while (--len) {
        ret += dis(gen);
    }
    return ret;
}

int main(int argc, char* argv[])
{
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::string a{"k"};
    std::string b{"sitt"};
    // Wiki example (http://en.wikipedia.org/wiki/Levenshtein_distance)
    assert(levenshtein_distance(a, b) == 4);
    a = "Saturday";
    b = "Sunday";
    assert(levenshtein_distance(a, b) == 3);
    a = "kitten";
    b = "sitting";
    assert(levenshtein_distance(a, b) == 3);

    if (argc == 3) {
        a = argv[1];
        b = argv[2];
    } else {
        std::uniform_int_distribution<int> dis{1, 100};
        a = rand_string(dis(gen));
        b = rand_string(dis(gen));
    }
    std::cout << a << "\n" << b << "\n";
    std::cout << levenshtein_distance(a, b) << "\n";
    assert(levenshtein_distance(a, b) == check_answer(a, b));
    return 0;
}
