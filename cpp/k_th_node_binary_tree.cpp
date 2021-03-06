// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>

using std::cout;
using std::endl;
using std::exception;
using std::length_error;
using std::make_unique;
using std::unique_ptr;

template<typename T>
struct Binary_tree_node {
    T data;
    unique_ptr<Binary_tree_node<T>> left, right;
    int size;
};

// @include
const Binary_tree_node<int>* FindKthNodeBinaryTree(
        const unique_ptr<Binary_tree_node<int>>& tree, int k)
{
    const auto* iter = tree.get();
    while (iter != nullptr) {
        int left_size = iter->left ? iter->left->size : 0;
        if (left_size + 1 < k) {  // k-th node must be in right subtree of iter.
            k -= (left_size + 1);
            iter = iter->right.get();
        } else if (left_size == k - 1) {  // k-th is iter itself.
            return iter;
        } else {  // k-th node must be in left subtree of iter.
            iter = iter->left.get();
        }
    }
    // If k is between 1 and the tree size, this line is unreachable.
    return nullptr;
}
// @exclude

int main(int argc, char* argv[])
{
    //  size field
    //      6
    //    2   3
    //  1    1 1
    //
    //  data field
    //      3
    //    2   5
    //  1    4 6
    auto root = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    root->size = 6;
    root->data = 3;
    root->left = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    root->left->size = 2;
    root->left->data = 2;
    root->left->left = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    root->left->left->size = 1;
    root->left->left->data = 1;
    root->right = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    root->right->size = 3;
    root->right->data = 5;
    root->right->left = make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    root->right->left->size = 1;
    root->right->left->data = 4;
    root->right->right =
            make_unique<Binary_tree_node<int>>(Binary_tree_node<int>());
    root->right->right->size = 1;
    root->right->right->data = 6;
    // 0th node does not exist - leftmost node is node 1
    assert(nullptr == FindKthNodeBinaryTree(root, 0));
    // should output 1
    assert(FindKthNodeBinaryTree(root, 1)->data == 1);
    cout << (FindKthNodeBinaryTree(root, 1))->data << "\n";
    // should output 2
    assert(FindKthNodeBinaryTree(root, 2)->data == 2);
    cout << (FindKthNodeBinaryTree(root, 2))->data << "\n";
    // should output 3
    assert(FindKthNodeBinaryTree(root, 3)->data == 3);
    cout << (FindKthNodeBinaryTree(root, 3))->data << "\n";
    // should output 4
    assert(FindKthNodeBinaryTree(root, 4)->data == 4);
    cout << (FindKthNodeBinaryTree(root, 4))->data << "\n";
    // should output 5
    assert(FindKthNodeBinaryTree(root, 5)->data == 5);
    cout << (FindKthNodeBinaryTree(root, 5))->data << "\n";
    // should output 6
    assert(FindKthNodeBinaryTree(root, 6)->data == 6);
    cout << (FindKthNodeBinaryTree(root, 6))->data << "\n";
    assert(nullptr == FindKthNodeBinaryTree(root, 7));
    return 0;
}
