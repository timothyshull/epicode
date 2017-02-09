// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <random>

#include "linked_list_prototype.h"
#include "reverse_linked_list_iterative.h"

// @include
std::shared_ptr<List_node<int>> zip_linked_list(const std::shared_ptr<List_node<int>>& list_head)
{
    if (!list_head || !list_head->next) {
        return list_head;
    }

    // Finds the second half of L.
    auto slow = list_head;
    auto fast = list_head;
    while (fast && fast->next) {
        fast = fast->next->next, slow = slow->next;
    }

    auto first_half_head = list_head;
    auto second_half_head = slow->next;
    slow->next = nullptr;  // Splits the list into two lists.

    second_half_head = reverse_linked_list(second_half_head);

    // Interleave the first half and the reversed of the second half.
    auto first_half_iter = first_half_head;
    auto second_half_iter = second_half_head;
    while (second_half_iter) {
        auto temp = second_half_iter->next;
        second_half_iter->next = first_half_iter->next;
        first_half_iter->next = second_half_iter;
        first_half_iter = first_half_iter->next->next;
        second_half_iter = temp;
    }
    return first_half_head;
}
// @exclude

int main(int argc, char* argv[])
{
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::shared_ptr<List_node<int>> head = nullptr;
    int n{};
    if (argc > 2) {
        for (int i{1}; i < argc; ++i) {
            auto curr = std::make_shared<List_node<int>>(List_node<int>{std::stoi(argv[i]), nullptr});
            curr->next = head;
            head = curr;
        }
    } else {
        if (argc == 2) {
            n = std::stoi(argv[1]);
        } else {
            std::uniform_int_distribution<int> dis{1, 1000};
            n = dis(gen);
        }
        for (int i = n; i >= 0; --i) {
            auto curr = std::make_shared<List_node<int>>(List_node<int>{i, nullptr});
            curr->next = head;
            head = curr;
        }
    }
    std::shared_ptr<List_node<int>> curr{zip_linked_list(head)};
    int idx{0};
    int pre{};
    while (curr) {
        if (argc <= 2) {
            if (idx % 2) { assert(pre + curr->data == n); }
        }
        ++idx;
        std::cout << curr->data << "\n";
        pre = curr->data;
        curr = curr->next;
    }
    return 0;
}
