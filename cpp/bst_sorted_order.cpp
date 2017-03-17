// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <stack>
#include <vector>

#include "bst_prototype.h"

// @include
std::vector<int> bst_in_sorted_order(const std::unique_ptr<BST_node<int>>& tree)
{
    std::stack<const BST_node<int>*> s;
    const auto* curr = tree.get();
    std::vector<int> result;

    while (!s.empty() || curr) {
        if (curr) {
            s.push(curr);
            // Going left.
            curr = curr->left.get();
        } else {
            // Going up.
            curr = s.top();
            s.pop();
            result.emplace_back(curr->data);
            // Going right.
            curr = curr->right.get();
        }
    }
    return result;
}
// @exclude

void simple_test()
{
    std::unique_ptr<BST_node<int>> tree{std::make_unique<BST_node<int>>(BST_node<int>{43, nullptr})};
    auto result = bst_in_sorted_order(tree);
    std::vector<int> golden_result = {43};
    assert(equal(golden_result.begin(), golden_result.end(), result.begin(), result.end()));
    tree->left = std::make_unique<BST_node<int>>(BST_node<int>{23, nullptr});
    result = bst_in_sorted_order(tree);
    golden_result = {23, 43};
    assert(equal(golden_result.begin(), golden_result.end(), result.begin(), result.end()));
}

int main(int argc, char* argv[])
{
    simple_test();
    //        43
    //    23     47
    //      37      53
    //    29  41
    //     31
    std::unique_ptr<BST_node<int>> tree = std::make_unique<BST_node<int>>(BST_node<int>{43, nullptr});
    tree->left = std::make_unique<BST_node<int>>(BST_node<int>{23, nullptr});
    tree->left->right = std::make_unique<BST_node<int>>(BST_node<int>{37, nullptr});
    tree->left->right->left = std::make_unique<BST_node<int>>(BST_node<int>{29, nullptr});
    tree->left->right->left->right = std::make_unique<BST_node<int>>(BST_node<int>{31, nullptr});
    tree->left->right->right = std::make_unique<BST_node<int>>(BST_node<int>{41, nullptr});
    tree->right = std::make_unique<BST_node<int>>(BST_node<int>{47, nullptr});
    tree->right->right = std::make_unique<BST_node<int>>(BST_node<int>{53, nullptr});
    auto result = bst_in_sorted_order(tree);
    std::vector<int> golden_res{23, 29, 31, 37, 41, 43, 47, 53};
    assert(equal(golden_res.begin(), golden_res.end(), result.begin(), result.end()));
    return 0;
}
