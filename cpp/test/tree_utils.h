#ifndef SOLUTIONS_TREE_UTILS_H
#define SOLUTIONS_TREE_UTILS_H

#include <memory>

#include "binary_tree_prototype.h"

template<class T>
unique_ptr<Binary_tree_node<T>> CreateNode(const T& value)
{
    return unique_ptr<Binary_tree_node<T>>(new Binary_tree_node<T>{value});
}

template<class T>
void TreeInsert(unique_ptr<Binary_tree_node<T>>& node, T value)
{
    if (!node) {
        node.reset(new Binary_tree_node<T>());
        node->data = value;
    } else {
        if (value <= node->data) {
            TreeInsert(node->left, value);
        } else {
            TreeInsert(node->right, value);
        }
    }
}

template<class T>
unique_ptr<Binary_tree_node<T>> BuildTree(const vector<T> values)
{
    unique_ptr<Binary_tree_node<T>> head;
    for (auto& x : values) {
        TreeInsert(head, x);
    }

    return move(head);
}

#endif //SOLUTIONS_TREE_UTILS_H
