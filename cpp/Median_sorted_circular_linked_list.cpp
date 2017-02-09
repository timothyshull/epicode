// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>

#include "linked_list_prototype.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::exception;
using std::length_error;
using std::make_shared;
using std::random_device;
using std::uniform_int_distribution;

// @include
double FindMedianSortedCircularLinkedList(
        const shared_ptr <List_node<int>>& arbitrary_node)
{
    // Checks if all nodes are identical and identifies the first smallest node.
    auto iter = arbitrary_node, first_smallest_node = arbitrary_node;
    int n = 0;
    do {
        if (iter->data > iter->next->data) {
            first_smallest_node = iter->next;
        }
        ++n, iter = iter->next;
    } while (iter != arbitrary_node);

    // Advances to the middle of the list.
    for (int i = 0; i < ((n - 1) / 2); ++i) {
        first_smallest_node = first_smallest_node->next;
    }
    return n % 2 ? first_smallest_node->data
                 : 0.5 * (first_smallest_node->data +
                          first_smallest_node->next->data);
}
// @exclude

void small_test()
{
    shared_ptr <List_node<int>> L = make_shared<List_node<int>>(
            List_node<int>{0, make_shared<List_node<int>>(List_node<int>{
                    2, make_shared<List_node<int>>(List_node<int>{
                            2, make_shared<List_node<int>>(
                                    List_node<int>{2, nullptr})})})});
    L->next->next->next->next = L;
    cout << FindMedianSortedCircularLinkedList(L->next->next) << "\n";
    assert(2 == FindMedianSortedCircularLinkedList(L->next->next));
}

int main(int argc, char* argv[])
{
    small_test();
    default_random_engine gen((random_device()) ());
    for (int times = 0; times < 1000; ++times) {
        int n;
        if (argc == 2) {
            n = atoi(argv[1]);
        } else {
            uniform_int_distribution<int> dis(1, 1000);
            n = dis(gen);
        }
        shared_ptr <List_node<int>> head;
        for (int i = n; i >= 0; --i) {
            auto curr = make_shared<List_node<int>>(List_node<int>{i, nullptr});
            curr->next = head;
            head = curr;
        }
        shared_ptr <List_node<int>> curr = head;
        if (curr != shared_ptr<List_node<int>>(nullptr)) {
            while (curr->next != shared_ptr<List_node<int>>(nullptr)) {
                curr = curr->next;
            }
            curr->next = head;  // make the list as a circular list.
        }
        double res = FindMedianSortedCircularLinkedList(head->next);
        cout << res << "\n";
        assert(res == 0.5 * n);
    }

    // test identical list.
    shared_ptr <List_node<int>> head;
    for (int i = 0; i < 10; ++i) {
        auto curr = make_shared<List_node<int>>(List_node<int>{5, nullptr});
        curr->next = head;
        head = curr;
    }
    shared_ptr <List_node<int>> curr = head;
    if (curr != shared_ptr<List_node<int>>(nullptr)) {
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = head;  // make the list as a circular list.
    }
    assert(5 == FindMedianSortedCircularLinkedList(head));
    return 0;
}
