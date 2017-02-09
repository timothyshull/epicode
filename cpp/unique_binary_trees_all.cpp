// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>

#include "binary_tree_prototype.h"

std::unique_ptr<Binary_tree_node<int>> clone(const std::unique_ptr<Binary_tree_node<int>>&);

// @include
std::vector<std::unique_ptr<Binary_tree_node<int>>> generate_all_binary_trees(int num_nodes)
{
    std::vector<std::unique_ptr<Binary_tree_node<int>>> result;
    if (num_nodes == 0) {  // Empty tree, add as an nullptr.
        result.emplace_back(nullptr);
    }

    for (int num_left_tree_nodes{0}; num_left_tree_nodes < num_nodes; ++num_left_tree_nodes) {
        int num_right_tree_nodes = num_nodes - 1 - num_left_tree_nodes;
        auto left_subtrees = generate_all_binary_trees(num_left_tree_nodes);
        auto right_subtrees = generate_all_binary_trees(num_right_tree_nodes);
        // Generates all combinations of left_subtrees and right_subtrees.
        for (auto& left : left_subtrees) {
            for (auto& right : right_subtrees) {
                result.emplace_back(std::make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{0, clone(left), clone(right)}));
            }
        }
    }
    return result;
}

std::unique_ptr<Binary_tree_node<int>> clone(const std::unique_ptr<Binary_tree_node<int>>& tree)
{
    return tree ? std::make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{0, clone(tree->left), clone(tree->right)}) : nullptr;
}
// @exclude

void small_test()
{
    assert(generate_all_binary_trees(1).size() == 1);
    assert(generate_all_binary_trees(2).size() == 2);
    assert(generate_all_binary_trees(3).size() == 5);
    assert(generate_all_binary_trees(4).size() == 14);
    assert(generate_all_binary_trees(5).size() == 42);
    assert(generate_all_binary_trees(10).size() == 16796);
}

int main(int argc, char** argv)
{
    small_test();
    std::random_device rd;
    std::default_random_engine gen{rd()};
    int n;
    if (argc == 2) {
        n = std::stoi(argv[1]);
    } else {
        std::uniform_int_distribution<int> dis{1, 10};
        n = dis(gen);
    }
    std::cout << "n = " << n << "\n";
    generate_all_binary_trees(n);
    return 0;
}
