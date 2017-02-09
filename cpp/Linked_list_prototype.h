// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_LINKED_LIST_PROTOTYPE_H_
#define SOLUTIONS_LINKED_LIST_PROTOTYPE_H_

#include <memory>

// @include
template<typename Data_type>
struct List_node {
    Data_type data;
    std::shared_ptr<List_node<Data_type>> next;
};
// @exclude
#endif  // SOLUTIONS_LINKED_LIST_PROTOTYPE_H_
