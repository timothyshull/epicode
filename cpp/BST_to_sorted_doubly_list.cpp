// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>

#include "bst_prototype_shared_ptr.h"

struct Head_and_tail;

Head_and_tail bst_to_doubly_linked_list_helper(const std::shared_ptr<BST_node<int>>&);

// @include
struct Head_and_tail {
    std::shared_ptr<BST_node<int>> head;
    std::shared_ptr<BST_node<int>> tail;
};

std::shared_ptr<BST_node<int>> bst_to_doubly_linked_list(const std::shared_ptr<BST_node<int>>& tree)
{
    return bst_to_doubly_linked_list_helper(tree).head;
}

// Transforms a BST into a sorted doubly linked list in-place,
// and return the head and tail of the list.
Head_and_tail bst_to_doubly_linked_list_helper(const std::shared_ptr<BST_node<int>>& tree)
{
    // Empty subtree.
    if (!tree) { return {nullptr, nullptr}; }

    // Recursively builds the list from left and right subtrees.
    Head_and_tail left = bst_to_doubly_linked_list_helper(tree->left);
    Head_and_tail right = bst_to_doubly_linked_list_helper(tree->right);

    // Appends tree to the list from left subtree.
    if (left.tail) { left.tail->right = tree; }
    tree->left = left.tail;

    // Appends the list from right subtree to tree.
    tree->right = right.head;
    if (right.head) { right.head->left = tree; }

    return {left.head ? left.head : tree, right.tail ? right.tail : tree};
}
// @exclude

int main(int argc, char* argv[])
{
    //    3
    //  2   5
    // 1   4 6
    auto root = std::make_shared<BST_node<int>>(BST_node<int>{3});
    root->left = std::make_shared<BST_node<int>>(BST_node<int>{2});
    root->left->left = std::make_shared<BST_node<int>>(BST_node<int>{1});
    root->right = std::make_shared<BST_node<int>>(BST_node<int>{5});
    root->right->left = std::make_shared<BST_node<int>>(BST_node<int>{4});
    root->right->right = std::make_shared<BST_node<int>>(BST_node<int>{6});
    std::shared_ptr<BST_node<int>> l{bst_to_doubly_linked_list(root)};
    std::shared_ptr<BST_node<int>> curr{l};
    int pre{std::numeric_limits<int>::min()};
    do {
        assert(pre <= curr->data);
        std::cout << curr->data << "\n";
        pre = curr->data;
        curr = curr->right;
    } while (curr);
    return 0;
}
