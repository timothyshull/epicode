// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <stack>
#include <vector>

#include "bst_prototype.h"

using std::cout;
using std::endl;
using std::make_unique;
using std::stack;
using std::unique_ptr;
using std::vector;

// @include
vector<int> bst_in_sorted_order(const unique_ptr<BST_node<int>>& tree)
{
    stack<const BST_node<int>*> s;
    const auto* curr = tree.get();
    vector<int> result;

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
    unique_ptr<BST_node<int>> tree = make_unique<BST_node<int>>(BST_node<int>{43, nullptr});
    auto result = bst_in_sorted_order(tree);
    vector<int> golden_result = {43};
    assert(equal(golden_result.begin(), golden_result.end(), result.begin(), result.end()));
    tree->left = make_unique<BST_node<int>>(BST_node<int>{23, nullptr});
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
    unique_ptr<BST_node<int>> tree = make_unique<BST_node<int>>(BST_node<int>{43, nullptr});
    tree->left = make_unique<BST_node<int>>(BST_node<int>{23, nullptr});
    tree->left->right = make_unique<BST_node<int>>(BST_node<int>{37, nullptr});
    tree->left->right->left = make_unique<BST_node<int>>(BST_node<int>{29, nullptr});
    tree->left->right->left->right = make_unique<BST_node<int>>(BST_node<int>{31, nullptr});
    tree->left->right->right = make_unique<BST_node<int>>(BST_node<int>{41, nullptr});
    tree->right = make_unique<BST_node<int>>(BST_node<int>{47, nullptr});
    tree->right->right = make_unique<BST_node<int>>(BST_node<int>{53, nullptr});
    auto result = bst_in_sorted_order(tree);
    vector<int> golden_res = {23, 29, 31, 37, 41, 43, 47, 53};
    assert(equal(golden_res.begin(), golden_res.end(), result.begin(), result.end()));
    return 0;
}
