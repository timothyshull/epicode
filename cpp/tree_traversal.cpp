// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <iostream>
#include <memory>

#include "binary_tree_prototype.h"

// @include
void traverse_tree(const std::unique_ptr<Binary_tree_node<int>>& root)
{
    if (root) {
        // Preorder: Processes the root before the traversals of left and right
        // children.
        std::cout << "Preorder: " << root->data << "\n";
        traverse_tree(root->left);
        // Inorder: Processes the root after the traversal of left child and
        // before the traversal of right child.
        std::cout << "Inorder: " << root->data << "\n";
        traverse_tree(root->right);
        // Postorder: Processes the root after the traversals of left and right
        // children.
        std::cout << "Postorder: " << root->data << "\n";
    }
}
// @exclude

int main(int argc, char* argv[])
{
    //      3
    //    2   5
    //  1   4   6
    auto tree = std::make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{3, nullptr, nullptr});
    tree->left = std::make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{2, nullptr, nullptr});
    tree->left->left = std::make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{1, nullptr, nullptr});
    tree->right = std::make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{5, nullptr, nullptr});
    tree->right->left = std::make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{4, nullptr, nullptr});
    tree->right->right = std::make_unique<Binary_tree_node<int>>(Binary_tree_node<int>{6, nullptr, nullptr});
    traverse_tree(tree);
    return 0;
}
