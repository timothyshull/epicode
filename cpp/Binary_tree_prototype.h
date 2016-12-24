// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_BINARY_TREE_PROTOTYPE_H_
#define SOLUTIONS_BINARY_TREE_PROTOTYPE_H_

#include <memory>

using std::unique_ptr;

// @include
template<typename T>
struct Binary_tree_node {
    T data;
    unique_ptr<Binary_tree_node<T>> left;
    unique_ptr<Binary_tree_node<T>> right;
};
// @exclude
#endif  // SOLUTIONS_BINARY_TREE_PROTOTYPE_H_
