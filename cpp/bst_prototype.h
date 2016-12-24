// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_BST_PROTOTYPE_H_
#define SOLUTIONS_BST_PROTOTYPE_H_

#include <memory>

using std::unique_ptr;

// @include
template<typename T>
struct BST_node {
    T data;
    unique_ptr<BST_node<T>> left;
    unique_ptr<BST_node<T>> right;
};
// @exclude
#endif  // SOLUTIONS_BST_PROTOTYPE_H_
