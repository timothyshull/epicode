// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

#include "Binary_tree_prototype.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::make_unique;
using std::unique_ptr;

bool CheckSymmetric(const unique_ptr<Binary_tree_node<int>>&,
                    const unique_ptr<Binary_tree_node<int>>&);

// @include
bool IsSymmetric(const unique_ptr<Binary_tree_node<int>>& tree)
{
    return tree == nullptr || CheckSymmetric(tree->left, tree->right);
}

bool CheckSymmetric(const unique_ptr<Binary_tree_node<int>>& subtree_0,
                    const unique_ptr<Binary_tree_node<int>>& subtree_1)
{
    if (subtree_0 == nullptr && subtree_1 == nullptr) {
        return true;
    } else if (subtree_0 != nullptr && subtree_1 != nullptr) {
        return subtree_0->data == subtree_1->data &&
               CheckSymmetric(subtree_0->left, subtree_1->right) &&
               CheckSymmetric(subtree_0->right, subtree_1->left);
    }
    // One subtree is empty, and the other is not.
    return false;
}
// @exclude

void simple_test()
{
    auto symm_tree = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    assert(IsSymmetric(symm_tree));
    symm_tree->left = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    assert(!IsSymmetric(symm_tree));
    symm_tree->right = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    assert(IsSymmetric(symm_tree));
    symm_tree->right->right =
            make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    assert(!IsSymmetric(symm_tree));
}

int main(int argc, char* argv[])
{
    simple_test();
    // Non symmetric tree test.
    //      x
    //    x   x
    //  x    x x
    auto non_symm_tree =
            make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    non_symm_tree->left =
            make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    non_symm_tree->left->left =
            make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    non_symm_tree->right =
            make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    non_symm_tree->right->left =
            make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    non_symm_tree->right->right =
            make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    assert(!IsSymmetric(non_symm_tree));
    cout << boolalpha << IsSymmetric(non_symm_tree) << "\n";
    // Symmetric tree test.
    unique_ptr<Binary_tree_node<int>> symm_tree =
            make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    symm_tree->left = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    symm_tree->right = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    assert(IsSymmetric(symm_tree) == true);
    cout << boolalpha << IsSymmetric(symm_tree) << "\n";
    // Empty tree test.
    symm_tree = nullptr;
    assert(IsSymmetric(symm_tree) == true);
    cout << boolalpha << IsSymmetric(symm_tree) << "\n";
    return 0;
}
