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
shared_ptr<List_node<int>> RemoveDuplicates(
        const shared_ptr<List_node<int>>& L)
{
    auto iter = L;
    while (iter) {
        // Uses next_distinct to find the next distinct value.
        auto next_distinct = iter->next;
        while (next_distinct && next_distinct->data == iter->data) {
            next_distinct = next_distinct->next;
        }
        iter->next = next_distinct;
        iter = next_distinct;
    }
    return L;
}
// @exclude

void simple_test()
{
    shared_ptr<List_node<int>> L = nullptr;
    auto result = RemoveDuplicates(L);
    assert(result == nullptr);
    L = make_shared<List_node<int>>(List_node<int>{123, nullptr});
    result = RemoveDuplicates(L);
    assert(result == L);
    L->next = make_shared<List_node<int>>(List_node<int>{123, nullptr});
    result = RemoveDuplicates(L);
    assert(result->next == nullptr);

    // Creating an invalid input, 123 -> 124 -> 123, algo will not detect dups!
    L->next = make_shared<List_node<int>>(List_node<int>{124, nullptr});
    L->next->next = make_shared<List_node<int>>(List_node<int>{123, nullptr});
    result = RemoveDuplicates(L);
    assert(result->data == 123 && result->next->data == 124 &&
           result->next->next->data == 123);
}

int main(int argc, char** argv)
{
    simple_test();
    shared_ptr<List_node<int>> L = make_shared<List_node<int>>(List_node<int>{
            2, make_shared<List_node<int>>(List_node<int>{
                    2, make_shared<List_node<int>>(List_node<int>{
                            2, make_shared<List_node<int>>(List_node<int>{
                                    2, make_shared<List_node<int>>(
                                            List_node<int>{2, nullptr})})})})});
    shared_ptr<List_node<int>> pre = nullptr;
    auto result = RemoveDuplicates(L);
    int count = 0;
    while (result) {
        ++count;
        if (pre) {
            assert(pre->data != result->data);
        }
        cout << result->data << "\n";
        pre = result;
        result = result->next;
    }
    assert(count == 1);
    return 0;
}
