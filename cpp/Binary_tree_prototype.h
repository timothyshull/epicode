// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_BINARY_TREE_PROTOTYPE_H_
#define SOLUTIONS_BINARY_TREE_PROTOTYPE_H_

#include <memory>

// @include
template<typename Data_type>
struct Binary_tree_node {
    Data_type data;
    std::unique_ptr<Binary_tree_node<Data_type>> left;
    std::unique_ptr<Binary_tree_node<Data_type>> right;
};
// @exclude
#endif  // SOLUTIONS_BINARY_TREE_PROTOTYPE_H_
