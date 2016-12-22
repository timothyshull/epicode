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
shared_ptr<List_node<int>> distinct_list(shared_ptr<List_node<int>>* L)
{
    shared_ptr<List_node<int>> pre = nullptr, now = *L;
    while (now) {
        if (now && now->next && now->data == now->next->data) {
            int target = now->data;
            while (now && now->data == target) {
                if (pre) {
                    pre->next = now->next;
                }
                if (now == *L) {
                    *L = now->next;
                }
                now = now->next;
            }
        } else {
            pre = now;
            now = now->next;
        }
    }
    return *L;
}
// @exclude

int main(int argc, char** argv)
{
    shared_ptr<List_node<int>> L;
    L = make_shared<List_node<int>>(List_node<int>{
            2, make_shared<List_node<int>>(List_node<int>{
                    2, make_shared<List_node<int>>(List_node<int>{
                            3, make_shared<List_node<int>>(List_node<int>{
                                    3, make_shared<List_node<int>>(
                                            List_node<int>{5, nullptr})})})})});
    shared_ptr<List_node<int>> pre = nullptr;
    auto result = distinct_list(&L);
    while (result) {
        if (pre) {
            assert(pre->data != result->data);
        }
        cout << result->data << "\n";
        pre = result;
        result = result->next;
    }
    return 0;
}
