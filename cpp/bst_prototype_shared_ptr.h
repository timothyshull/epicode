// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_BST_PROTOTYPE_SHARED_PTR_H_
#define SOLUTIONS_BST_PROTOTYPE_SHARED_PTR_H_

#include <memory>

using std::shared_ptr;

// @include
template<typename T>
struct BST_node {
    T data;
    shared_ptr<BST_node<T>> left;
    shared_ptr<BST_node<T>> right;
};
// @exclude
#endif  // SOLUTIONS_BST_PROTOTYPE_SHARED_PTR_H_
