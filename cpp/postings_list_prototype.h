// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#ifndef SOLUTIONS_POSTINGS_LIST_PROTOTYPE_H_
#define SOLUTIONS_POSTINGS_LIST_PROTOTYPE_H_

#include <memory>

using std::shared_ptr;

// @include
class Posting_list_node {
public:
    int order;
    shared_ptr<Posting_list_node> next, jump;
};
// @exclude
#endif  // SOLUTIONS_POSTINGS_LIST_PROTOTYPE_H_
