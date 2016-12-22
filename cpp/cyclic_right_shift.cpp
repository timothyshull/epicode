// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

#include "linked_list_prototype.h"

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

// @include
shared_ptr<List_node<int>> CyclicallyRightShiftList(
        shared_ptr<List_node<int>> L, int k)
{
    if (L == nullptr) {
        return L;
    }

    // Computes the length of L and the tail.
    auto tail = L;
    int n = 1;
    while (tail->next) {
        ++n, tail = tail->next;
    }
    k %= n;
    if (k == 0) {
        return L;
    }

    tail->next = L;  // Makes a cycle by connecting the tail to the head.
    int steps_to_new_head = n - k;
    auto new_tail = tail;
    while (steps_to_new_head--) {
        new_tail = new_tail->next;
    }
    auto new_head = new_tail->next;
    new_tail->next = nullptr;
    return new_head;
}
// @exclude

void simple_test()
{
    shared_ptr<List_node<int>> L;
    L = make_shared<List_node<int>>(List_node<int>{1, nullptr});
    auto result = CyclicallyRightShiftList(L, 2);
    assert(result == L);
    L->next = make_shared<List_node<int>>(List_node<int>{2, nullptr});
    result = CyclicallyRightShiftList(L, 2);
    assert(result == L);
    result = CyclicallyRightShiftList(L, 3);
    assert(result->next == L);
}

int main(int argc, char* argv[])
{
    simple_test();
    shared_ptr<List_node<int>> L;
    L = make_shared<List_node<int>>(List_node<int>{
            1, make_shared<List_node<int>>(List_node<int>{
                    2, make_shared<List_node<int>>(List_node<int>{3, nullptr})})});
    auto result = CyclicallyRightShiftList(L, 2);
    assert(result->data == 2 && result->next->data == 3 &&
           result->next->next->data == 1 && !result->next->next->next);
    return 0;
}
