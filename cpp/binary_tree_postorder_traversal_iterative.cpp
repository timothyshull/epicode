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
// We use stack and previous node pointer to simulate postorder traversal.
vector<int> postorder_traversal(const unique_ptr<Binary_tree_node<int>>& tree)
{
    if (tree == nullptr) {  // Empty tree.
        return {};
    }

    stack<Binary_tree_node<int>*> path;
    Binary_tree_node<int>* prev = nullptr;
    path.emplace(tree.get());
    vector<int> postorder_sequence;
    while (!path.empty()) {
        auto curr = path.top();
        if (prev == nullptr || prev->left.get() == curr ||
            prev->right.get() == curr) {
            // We came down to curr from prev.
            if (curr->left != nullptr) {  // Traverse left.
                path.emplace(curr->left.get());
            } else if (curr->right != nullptr) {  // Traverse right.
                path.emplace(curr->right.get());
            } else {  // Leaf node, so visit current node.
                postorder_sequence.emplace_back(curr->data);
                path.pop();
            }
        } else if (curr->left.get() == prev) {
            // Done with left, so now traverse right.
            if (curr->right != nullptr) {
                path.emplace(curr->right.get());
            } else {  // No right child, so visit curr.
                postorder_sequence.emplace_back(curr->data);
                path.pop();
            }
        } else {
            // finished traversing left and right, so visit curr.
            postorder_sequence.emplace_back(curr->data);
            path.pop();
        }
        prev = curr;
    }
    return postorder_sequence;
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
    auto res = postorder_traversal(tree), golden_res = generate_postorder(tree);
    assert(equal(res.cbegin(), res.cend(), golden_res.cbegin(), golden_res.cend()));
    return 0;
}
