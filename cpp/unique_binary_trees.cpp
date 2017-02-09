// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>

// @include
int num_unique_binary_trees(int n)
{
    std::vector<int> num(static_cast<std::vector<int>::size_type>(n + 1), 0);
    num[0] = 1;
    for (int i{1}; i <= n; ++i) {
        for (int j{0}; j < i; ++j) {
            num[i] += num[j] * num[i - j - 1];
        }
    }
    return num.back();
}
// @exclude

int main(int argc, char** argv)
{
    assert(num_unique_binary_trees(10) == 16796);
    assert(num_unique_binary_trees(9) == 4862);
    assert(num_unique_binary_trees(2) == 2);
    assert(num_unique_binary_trees(3) == 5);
    
    std::random_device rd;
    std::default_random_engine gen{rd()};
    
    int n;
    if (argc == 2) {
        n = std::stoi(argv[1]);
    } else {
        std::uniform_int_distribution<int> dis{1, 15};
        n = dis(gen);
    }
    
    std::cout << "n = " << n << "\n";
    std::cout << num_unique_binary_trees(n) << "\n";
    return 0;
}
