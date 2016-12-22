// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <memory>
#include <vector>

#include "linked_list_prototype.h"

using std::make_shared;
using std::shared_ptr;
using std::vector;

// @include
// Delete the node past this one. Assume node is not a tail.
void DeleteAfter(const shared_ptr<List_node<int>>& node)
{
    node->next = node->next->next;
}
// @exclude

void CheckAnswer(shared_ptr<List_node<int>> L, const vector<int>& vals)
{
    for (int i = 0; i < vals.size(); ++i) {
        assert(L->data == vals[i]);
        L = L->next;
    }
    assert(!L);
}

int main(int argc, char* argv[])
{
    shared_ptr<List_node<int>> L;
    L = make_shared<List_node<int>>(List_node<int>{
            2, make_shared<List_node<int>>(List_node<int>{
                    4, make_shared<List_node<int>>(List_node<int>{3, nullptr})})});
    DeleteAfter(L);
    CheckAnswer(L, {2, 3});
    DeleteAfter(L);
    CheckAnswer(L, {2});
    return 0;
}
