// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

#include "linked_list_prototype.h"
#include "merge_sorted_lists.h"  // uses AppendNode().

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

// @include
shared_ptr<List_node<int>> ListPivoting(const shared_ptr<List_node<int>>& L,
                                       int x)
{
    shared_ptr<List_node<int>> less_head(new List_node<int>),
            equal_head(new List_node<int>), greater_head(new List_node<int>);
    shared_ptr<List_node<int>> less_iter = less_head, equal_iter = equal_head,
            greater_iter = greater_head;
    // Populates the three lists.
    shared_ptr<List_node<int>> iter = L;
    while (iter) {
        AppendNode(&iter, iter->data < x
                          ? &less_iter
                          : iter->data == x ? &equal_iter : &greater_iter);
    }
    // Combines the three lists.
    greater_iter->next = nullptr;
    equal_iter->next = greater_head->next;
    less_iter->next = equal_head->next;
    return less_head->next;
}
// @exclude

void simple_test()
{
    shared_ptr<List_node<int>> L =
            make_shared<List_node<int>>(List_node<int>{0, nullptr});
    auto result = ListPivoting(L, 0);
    assert(result == L);
    result = ListPivoting(L, 1);
    assert(result == L);
    result = ListPivoting(L, -1);
    assert(result == L);

    L = make_shared<List_node<int>>(List_node<int>{
            2, make_shared<List_node<int>>(List_node<int>{0, nullptr})});
    result = ListPivoting(L, -1);

    L = make_shared<List_node<int>>(List_node<int>{
            2, make_shared<List_node<int>>(List_node<int>{0, nullptr})});
    result = ListPivoting(L, 1);
    assert(result->data == 0 && result->next->data == 2);

    L = make_shared<List_node<int>>(List_node<int>{
            2, make_shared<List_node<int>>(List_node<int>{
                    0, make_shared<List_node<int>>(List_node<int>{-2, nullptr})})});
    result = ListPivoting(L, 1);
    assert(result->data == 0 && result->next->data == -2 &&
           result->next->next->data == 2);
}

int main(int argc, char** argv)
{
    simple_test();
    shared_ptr<List_node<int>> L;
    L = make_shared<List_node<int>>(List_node<int>{
            1, make_shared<List_node<int>>(List_node<int>{
                    4, make_shared<List_node<int>>(List_node<int>{
                            3, make_shared<List_node<int>>(List_node<int>{
                                    2, make_shared<List_node<int>>(
                                            List_node<int>{5, nullptr})})})})});
    int x = 4;
    auto result = ListPivoting(L, x);
    cout << "\n";
    bool before_x = true;
    while (result) {
        if (result->data >= x) {
            before_x = false;
        }
        if (before_x) {
            assert(result->data < x);
        } else {
            assert(result->data >= x);
        }
        cout << result->data << "\n";
        result = result->next;
    }
    return 0;
}
