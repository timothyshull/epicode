// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_BST_PARENT_PROTOTYPE_H_
#define SOLUTIONS_BST_PARENT_PROTOTYPE_H_

#include <iostream>
#include <memory>

// @include
template<typename Data_type>
struct BSTNode {
    Data_type data;
    std::unique_ptr<BSTNode<T>> left;
    std::unique_ptr<BSTNode<T>> right;
    BSTNode<T>* parent;
};
// @exclude
#endif  // SOLUTIONS_BST_PARENT_PROTOTYPE_H_
