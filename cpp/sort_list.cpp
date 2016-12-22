// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <string>

#include "linked_list_prototype.h"
#include "merge_sorted_lists.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::make_shared;
using std::numeric_limits;
using std::random_device;
using std::stoi;
using std::uniform_int_distribution;

// @include
shared_ptr<List_node<int>> StableSortList(shared_ptr<List_node<int>> L)
{
    // Base cases: L is empty or a single node, nothing to do.
    if (L == nullptr || L->next == nullptr) {
        return L;
    }

    // Find the midpoint of L using a slow and a fast pointer.
    shared_ptr<List_node<int>> pre_slow = nullptr, slow = L, fast = L;
    while (fast && fast->next) {
        pre_slow = slow;
        fast = fast->next->next, slow = slow->next;
    }

    pre_slow->next = nullptr;  // Splits the list into two equal-sized lists.

    return MergeTwoSortedLists(StableSortList(L), StableSortList(slow));
}
// @exclude

int main(int argc, char* argv[])
{
    default_random_engine gen((random_device()) ());
    for (int times = 0; times < 10000; ++times) {
        shared_ptr<List_node<int>> L = nullptr;
        int n;
        uniform_int_distribution<int> dis(0, 99);
        if (argc == 2) {
            n = stoi(argv[1]);
        } else {
            n = dis(gen);
        }
        for (int i = n; i > 0; --i) {
            shared_ptr<List_node<int>> temp =
                    make_shared<List_node<int>>(List_node<int>{dis(gen), nullptr});
            temp->next = L;
            L = temp;
        }

        auto sorted_head = StableSortList(L);
        int count = 0;
        int pre = numeric_limits<int>::min();
        while (sorted_head) {
            assert(pre <= sorted_head->data);
            pre = sorted_head->data;
            sorted_head = sorted_head->next;
            ++count;
        }
        assert(count == n);
    }
    return 0;
}
