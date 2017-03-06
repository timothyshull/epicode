// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_BST_PROTOTYPE_H_
#define SOLUTIONS_BST_PROTOTYPE_H_

#include <memory>

// @include
template<typename Data_type>
struct BST_node {
    Data_type data;
    std::unique_ptr<BST_node<Data_type>> left;
    std::unique_ptr<BST_node<Data_type>> right;
};
// @exclude
#endif  // SOLUTIONS_BST_PROTOTYPE_H_
