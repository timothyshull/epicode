// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

#include "binary_tree_prototype.h"

using std::cout;
using std::endl;
using std::make_unique;
using std::unique_ptr;
using std::vector;

vector<int> result;

// @include
void InorderTraversal(const unique_ptr<Binary_tree_node<int>>& tree)
{
    auto* iter = tree.get();
    while (iter) {
        if (iter->left.get()) {
            // Finds the predecessor of iter.
            auto& pre = iter->left;
            while (pre->right && pre->right.get() != iter) {
                pre.reset(pre->right.get());
            }

            // Processes the successor link.
            if (pre->right) {  // pre->right.get() == iter.
                // Reverts the successor link if predecessor's successor is iter.
                pre->right.release();
                cout << iter->data << "\n";
                // @exclude
                result.emplace_back(iter->data);
                // @include
                iter = iter->right.get();
            } else {  // If predecessor's successor is not iter.
                pre->right.reset(iter);
                iter = iter->left.get();
            }
        } else {
            cout << iter->data << "\n";
            // @exclude
            result.emplace_back(iter->data);
            // @include
            iter = iter->right.get();
        }
    }
}
// @exclude

int main(int argc, char* argv[])
{
    //      3
    //    2   5
    //  1    4 6
    unique_ptr<Binary_tree_node<int>> tree =
            make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{3});
    tree->left = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{2});
    tree->left->left = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{1});
    tree->right = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{5});
    tree->right->left =
            make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{4});
    tree->right->right =
            make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{6});
    // should output 1 2 3 4 5 6
    InorderTraversal(tree);
    vector<int> golden_res = {1, 2, 3, 4, 5, 6};
    assert(equal(result.begin(), result.end(), golden_res.begin(),
                 golden_res.end()));
    return 0;
}
