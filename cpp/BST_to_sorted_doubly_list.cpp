// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <memory>

#include "bst_prototype_shared_ptr.h"

using std::cout;
using std::endl;
using std::make_shared;
using std::numeric_limits;
using std::shared_ptr;

struct HeadAndTail;

HeadAndTail bst_to_doubly_linked_list_helper(const shared_ptr<BST_node<int>>&);

// @include
struct HeadAndTail {
    shared_ptr<BST_node<int>> head, tail;
};

shared_ptr<BST_node<int>> bst_to_doubly_linked_list(const shared_ptr<BST_node<int>>& tree)
{
    return bst_to_doubly_linked_list_helper(tree).head;
}

// Transforms a BST into a sorted doubly linked list in-place,
// and return the head and tail of the list.
HeadAndTail bst_to_doubly_linked_list_helper(const shared_ptr<BST_node<int>>& tree)
{
    // Empty subtree.
    if (!tree) {
        return {nullptr, nullptr};
    }

    // Recursively builds the list from left and right subtrees.
    HeadAndTail left = bst_to_doubly_linked_list_helper(tree->left);
    HeadAndTail right = bst_to_doubly_linked_list_helper(tree->right);

    // Appends tree to the list from left subtree.
    if (left.tail) {
        left.tail->right = tree;
    }
    tree->left = left.tail;

    // Appends the list from right subtree to tree.
    tree->right = right.head;
    if (right.head) {
        right.head->left = tree;
    }

    return {left.head ? left.head : tree, right.tail ? right.tail : tree};
}
// @exclude

int main(int argc, char* argv[])
{
    //    3
    //  2   5
    // 1   4 6
    auto root = make_shared<BST_node<int>>(BST_node<int>{3});
    root->left = make_shared<BST_node<int>>(BST_node<int>{2});
    root->left->left = make_shared<BST_node<int>>(BST_node<int>{1});
    root->right = make_shared<BST_node<int>>(BST_node<int>{5});
    root->right->left = make_shared<BST_node<int>>(BST_node<int>{4});
    root->right->right = make_shared<BST_node<int>>(BST_node<int>{6});
    shared_ptr<BST_node<int>> L = bst_to_doubly_linked_list(root);
    shared_ptr<BST_node<int>> curr = L;
    int pre = numeric_limits<int>::min();
    do {
        assert(pre <= curr->data);
        cout << curr->data << "\n";
        pre = curr->data;
        curr = curr->right;
    } while (curr);
    return 0;
}
