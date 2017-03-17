// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>

#include "bst_prototype.h"

using std::make_unique;
using std::unique_ptr;

// @include
BST_node<int>* FindFirstGreaterThanK(const unique_ptr<BST_node<int>>& tree,
                                     int k)
{
    BST_node<int>* subtree = tree.get(), * first_so_far = nullptr;
    while (subtree) {
        if (subtree->data > k) {
            first_so_far = subtree;
            subtree = subtree->left.get();
        } else {  // Root and all keys in left subtree are <= k, so skip them.
            subtree = subtree->right.get();
        }
    }
    return first_so_far;
}
// @exclude

int main(int argc, char* argv[])
{
    //    3
    //  2   5
    // 1   4 7
    auto tree = make_unique<BST_node<int>>(BST_node<int>{3});
    tree->left = make_unique<BST_node<int>>(BST_node<int>{2});
    tree->left->left = make_unique<BST_node<int>>(BST_node<int>{1});
    tree->right = make_unique<BST_node<int>>(BST_node<int>{5});
    tree->right->left = make_unique<BST_node<int>>(BST_node<int>{4});
    tree->right->right = make_unique<BST_node<int>>(BST_node<int>{7});
    assert(FindFirstGreaterThanK(tree, 1) == tree->left.get());
    assert(FindFirstGreaterThanK(tree, 5) == tree->right->right.get());
    assert(FindFirstGreaterThanK(tree, 6) == tree->right->right.get());
    assert(!FindFirstGreaterThanK(tree, 7));
    return 0;
}
