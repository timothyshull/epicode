// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "linked_list_prototype.h"

using std::cout;
using std::endl;
using std::exception;
using std::length_error;
using std::make_shared;
using std::shared_ptr;

// @include
shared_ptr<List_node<int>> add_two_numbers(shared_ptr<List_node<int>> L1, shared_ptr<List_node<int>> L2)
{
    shared_ptr<List_node<int>> dummy_head(new List_node<int>);
    auto place_iter = dummy_head;
    int carry = 0;
    while (L1 || L2) {
        int sum = carry;
        if (L1) {
            sum += L1->data;
            L1 = L1->next;
        }
        if (L2) {
            sum += L2->data;
            L2 = L2->next;
        }
        place_iter->next =
                make_shared<List_node<int>>(List_node<int>{sum % 10, nullptr});
        carry = sum / 10, place_iter = place_iter->next;
    }
    // carry cannot exceed 1, so we never need to add more than one node.
    if (carry) {
        place_iter->next =
                make_shared<List_node<int>>(List_node<int>{carry, nullptr});
    }
    return dummy_head->next;
}
// @exclude

void simple_test()
{
    shared_ptr<List_node<int>> L;
    L = make_shared<List_node<int>>(List_node<int>{
            2, make_shared<List_node<int>>(List_node<int>{
                    4, make_shared<List_node<int>>(List_node<int>{3, nullptr})})});
    shared_ptr<List_node<int>> R;
    R = make_shared<List_node<int>>(List_node<int>{0, nullptr});
    auto S = add_two_numbers(L, R);
    assert(S->data == 2 && S->next->data == 4 && S->next->next->data == 3);

    L = make_shared<List_node<int>>(List_node<int>{
            3, make_shared<List_node<int>>(List_node<int>{
                    4, make_shared<List_node<int>>(List_node<int>{2, nullptr})})});
    R = make_shared<List_node<int>>(List_node<int>{
            7, make_shared<List_node<int>>(List_node<int>{
                    5, make_shared<List_node<int>>(List_node<int>{7, nullptr})})});
    S = add_two_numbers(L, R);
    assert(S->data == 0 && S->next->data == 0 && S->next->next->data == 0 &&
           S->next->next->next->data == 1);

    L = make_shared<List_node<int>>(List_node<int>{1, nullptr});
    R = make_shared<List_node<int>>(List_node<int>{1, nullptr});
    S = add_two_numbers(L, R);
    assert(S->data == 2 && S->next == nullptr);

    L = make_shared<List_node<int>>(List_node<int>{5, nullptr});
    R = make_shared<List_node<int>>(List_node<int>{5, nullptr});
    S = add_two_numbers(L, R);
    assert(S->data == 0 && S->next->data == 1 && S->next->next == nullptr);
}

int main(int argc, char* argv[])
{
    simple_test();
    shared_ptr<List_node<int>> L;
    L = make_shared<List_node<int>>(List_node<int>{
            2, make_shared<List_node<int>>(List_node<int>{
                    4, make_shared<List_node<int>>(List_node<int>{3, nullptr})})});
    shared_ptr<List_node<int>> R;
    R = make_shared<List_node<int>>(List_node<int>{
            5, make_shared<List_node<int>>(List_node<int>{
                    6, make_shared<List_node<int>>(List_node<int>{7, nullptr})})});
    auto S = add_two_numbers(L, R);
    assert(S->data == 7 && S->next->data == 0 && S->next->next->data == 1 &&
           S->next->next->next->data == 1);
    L = make_shared<List_node<int>>(List_node<int>{
            9, make_shared<List_node<int>>(List_node<int>{9, nullptr})});
    R = make_shared<List_node<int>>(List_node<int>{9, nullptr});
    S = add_two_numbers(L, R);
    assert(S->data == 8 && S->next->data == 0 && S->next->next->data == 1);
    return 0;
}
