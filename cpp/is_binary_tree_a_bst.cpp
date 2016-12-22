// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <memory>

#include "binary_tree_prototype.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::make_unique;
using std::numeric_limits;
using std::unique_ptr;

bool AreKeysInRange(const unique_ptr<Binary_tree_node<int>>&, int, int);

// @include
bool IsBinaryTreeBST(const unique_ptr<Binary_tree_node<int>>& tree)
{
    return AreKeysInRange(tree, numeric_limits<int>::min(),
                          numeric_limits<int>::max());
}

bool AreKeysInRange(const unique_ptr<Binary_tree_node<int>>& tree,
                    int low_range, int high_range)
{
    if (tree == nullptr) {
        return true;
    } else if (tree->data < low_range || tree->data > high_range) {
        return false;
    }

    return AreKeysInRange(tree->left, low_range, tree->data) &&
           AreKeysInRange(tree->right, tree->data, high_range);
}
// @exclude

int main(int argc, char* argv[])
{
    //      3
    //    2   5
    //  1    4 6
    auto tree = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{3});
    tree->left = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{2});
    tree->left->left = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{1});
    tree->right = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{5});
    tree->right->left =
            make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{4});
    tree->right->right =
            make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{6});
    // should output true.
    assert(IsBinaryTreeBST(tree) == true);
    cout << boolalpha << IsBinaryTreeBST(tree) << "\n";
    //      10
    //    2   5
    //  1    4 6
    tree->data = 10;
    // should output false.
    assert(!IsBinaryTreeBST(tree));
    cout << boolalpha << IsBinaryTreeBST(tree) << "\n";
    // should output true.
    assert(IsBinaryTreeBST(nullptr) == true);
    cout << boolalpha << IsBinaryTreeBST(nullptr) << "\n";
    return 0;
}
