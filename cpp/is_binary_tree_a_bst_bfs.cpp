// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>

#include "Binary_tree_prototype.h"

using std::boolalpha;
using std::cout;
using std::endl;
using std::make_unique;
using std::numeric_limits;
using std::queue;
using std::unique_ptr;

// @include
struct QueueEntry {
    const unique_ptr<Binary_tree_node<int>>& tree_node;
    int lower_bound, upper_bound;
};

bool IsBinaryTreeBST(const unique_ptr<Binary_tree_node<int>>& tree)
{
    queue<QueueEntry> BFS_queue;
    BFS_queue.emplace(QueueEntry{tree, numeric_limits<int>::min(),
                                 numeric_limits<int>::max()});

    while (!BFS_queue.empty()) {
        if (BFS_queue.front().tree_node.get()) {
            if (BFS_queue.front().tree_node->data < BFS_queue.front().lower_bound ||
                BFS_queue.front().tree_node->data > BFS_queue.front().upper_bound) {
                return false;
            }

            BFS_queue.emplace(QueueEntry{BFS_queue.front().tree_node->left,
                                         BFS_queue.front().lower_bound,
                                         BFS_queue.front().tree_node->data});
            BFS_queue.emplace(QueueEntry{BFS_queue.front().tree_node->right,
                                         BFS_queue.front().tree_node->data,
                                         BFS_queue.front().upper_bound});
        }
        BFS_queue.pop();
    }
    return true;
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
    // should output true
    assert(IsBinaryTreeBST(tree) == true);
    cout << boolalpha << IsBinaryTreeBST(tree) << "\n";
    //      10
    //    2   5
    //  1    4 6
    tree->data = 10;
    // should output false
    assert(!IsBinaryTreeBST(tree));
    cout << boolalpha << IsBinaryTreeBST(tree) << "\n";
    // empty tree, should output true
    assert(IsBinaryTreeBST(nullptr) == true);
    cout << boolalpha << IsBinaryTreeBST(nullptr) << "\n";
    return 0;
}
