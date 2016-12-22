// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <utility>

#include "binary_tree_prototype.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::make_unique;
using std::max;
using std::pair;
using std::tie;
using std::unique_ptr;

struct Balanced_status_with_height;

Balanced_status_with_height check_balanced(const unique_ptr<Binary_tree_node<int>>&);

// @include
struct Balanced_status_with_height {
    bool balanced;
    int height;
};

bool is_balanced(const unique_ptr<Binary_tree_node<int>>& tree)
{
    return check_balanced(tree).balanced;
}

// First value of the return value indicates if tree is balanced, and if
// balanced the second value of the return value is the height of tree.
Balanced_status_with_height check_balanced(const unique_ptr<Binary_tree_node<int>>& tree)
{
    if (tree == nullptr) {
        return {true, -1};  // Base case.
    }

    auto left_result = check_balanced(tree->left);
    if (!left_result.balanced) {
        return {false, 0};  // Left subtree is not balanced.
    }
    auto right_result = check_balanced(tree->right);
    if (!right_result.balanced) {
        return {false, 0};  // Right subtree is not balanced.
    }

    bool is_balanced = abs(left_result.height - right_result.height) <= 1;
    int height = max(left_result.height, right_result.height) + 1;
    return {is_balanced, height};
}
// @exclude

int main(int argc, char* argv[])
{
    //  balanced binary tree test
    //      3
    //    2   5
    //  1    4 6
    unique_ptr<Binary_tree_node<int>> tree = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    tree->left = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    tree->left->left = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    tree->right = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    tree->right->left = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    tree->right->right = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    assert(is_balanced(tree));
    cout << boolalpha << is_balanced(tree) << "\n";
    // Non-balanced binary tree test.
    tree = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    tree->left = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    tree->left->left = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    assert(!is_balanced(tree));
    cout << boolalpha << is_balanced(tree) << "\n";
    return 0;
}
