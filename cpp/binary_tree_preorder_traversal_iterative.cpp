// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <stack>
#include <vector>

#include "binary_tree_prototype.h"
#include "binary_tree_utils.h"

using std::cout;
using std::endl;
using std::equal;
using std::make_unique;
using std::stack;
using std::unique_ptr;
using std::vector;

// @include
vector<int> preorder_traversal(const unique_ptr<Binary_tree_node<int>>& tree)
{
    stack<Binary_tree_node<int>*> path;
    path.emplace(tree.get());
    vector<int> result;
    while (!path.empty()) {
        auto curr = path.top();
        path.pop();
        if (curr != nullptr) {
            result.emplace_back(curr->data);
            path.emplace(curr->right.get());
            path.emplace(curr->left.get());
        }
    }
    return result;
}
// @exclude

int main(int argc, char** argv)
{
    //      3
    //    2   5
    //  1    4 6
    unique_ptr<Binary_tree_node<int>> tree = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{3, nullptr, nullptr});
    tree->left = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{2, nullptr, nullptr});
    tree->left->left = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{1, nullptr, nullptr});
    tree->right = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{5, nullptr, nullptr});
    tree->right->left = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{4, nullptr, nullptr});
    tree->right->right = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{6, nullptr, nullptr});
    auto res = preorder_traversal(tree), golden_res = generate_preorder(tree);
    assert(equal(res.cbegin(), res.cend(), golden_res.cbegin(), golden_res.cend()));
    return 0;
}
