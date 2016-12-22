// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <memory>

#include "Linked_list_prototype.h"

using std::make_shared;
using std::shared_ptr;

// @include
shared_ptr<List_node<int>> SearchList(shared_ptr<List_node<int>> L, int key)
{
    while (L && L->data != key) {
        L = L->next;
    }
    // If key was not present in the list, L will have become null.
    return L;
}
// @exclude

int main(int argc, char* argv[])
{
    shared_ptr<List_node<int>> L;
    L = make_shared<List_node<int>>(List_node<int>{
            2, make_shared<List_node<int>>(List_node<int>{
                    4, make_shared<List_node<int>>(List_node<int>{3, nullptr})})});
    assert(L == SearchList(L, 2));
    assert(L->next == SearchList(L, 4));
    assert(L->next->next == SearchList(L, 3));
    assert(nullptr == SearchList(L, 100));
    return 0;
}
