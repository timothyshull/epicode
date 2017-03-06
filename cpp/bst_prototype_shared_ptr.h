// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_BST_PROTOTYPE_SHARED_PTR_H_
#define SOLUTIONS_BST_PROTOTYPE_SHARED_PTR_H_

#include <memory>

// @include
template<typename Data_type>
struct BST_node {
    Data_type data;
    std::shared_ptr<BST_node<Data_type>> left;
    std::shared_ptr<BST_node<Data_type>> right;
};
// @exclude
#endif  // SOLUTIONS_BST_PROTOTYPE_SHARED_PTR_H_
