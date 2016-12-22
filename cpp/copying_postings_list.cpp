// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <random>

#include "postings_list_prototype.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::make_shared;
using std::random_device;
using std::shared_ptr;
using std::uniform_int_distribution;

// @include
shared_ptr<Posting_list_node> CopyPostingsList(
        const shared_ptr<Posting_list_node>& L)
{
    if (L == nullptr) {
        return nullptr;
    }

    // Stage 1: Makes a copy of the original list without assigning the jump
    //          field, and creates the mapping for each node in the original
    //          list to the copied list.
    auto iter = L;
    while (iter) {
        auto new_node = make_shared<Posting_list_node>(
                Posting_list_node{iter->order, iter->next, nullptr});
        iter->next = new_node;
        iter = new_node->next;
    }

    // Stage 2: Assigns the jump field in the copied list.
    iter = L;
    while (iter) {
        if (iter->jump) {
            iter->next->jump = iter->jump->next;
        }
        iter = iter->next->next;
    }

    // Stage 3: Reverts the original list, and assigns the next field of
    //          the copied list.
    iter = L;
    auto new_list_head = iter->next;
    while (iter->next) {
        auto temp = iter->next;
        iter->next = temp->next;
        iter = temp;
    }
    return new_list_head;
}
// @exclude

template<typename T>
void CheckPostingsListEqual(shared_ptr<Posting_list_node> a,
                            shared_ptr<Posting_list_node> b)
{
    while (a && b) {
        cout << a->order << ' ';
        assert(a->order == b->order);
        assert((a->jump == shared_ptr<Posting_list_node>(nullptr) &&
                b->jump == shared_ptr<Posting_list_node>(nullptr)) ||
               (a->jump && b->jump && a->jump->order == b->jump->order));
        if (a->jump) {
            cout << a->jump->order;
        }
        cout << "\n";
        a = a->next, b = b->next;
    }
    assert(a == shared_ptr<Posting_list_node>(nullptr) &&
           b == shared_ptr<Posting_list_node>(nullptr));
}

int main(int argc, char* argv[])
{
    default_random_engine gen((random_device()) ());
    for (int times = 0; times < 1000; ++times) {
        int n;
        if (argc == 2) {
            n = atoi(argv[1]);
        } else {
            uniform_int_distribution<int> n_dis(1, 1000);
            n = n_dis(gen);
        }
        shared_ptr<Posting_list_node> L = nullptr;
        shared_ptr<Posting_list_node> curr = L;
        for (int i = 0; i < n; ++i) {
            auto temp = make_shared<Posting_list_node>(Posting_list_node{i, nullptr});
            if (L) {
                curr->next = temp;
                curr = temp;
            } else {
                curr = L = temp;
            }
            // Randomly assigned a jump node.
            uniform_int_distribution<int> dis(0, i + 1);
            int jump_num = dis(gen);
            shared_ptr<Posting_list_node> jump = L;
            while (jump_num--) {
                jump = jump->next;
            }
            temp->jump = jump;
        }
        shared_ptr<Posting_list_node> copied = CopyPostingsList(L);
        CheckPostingsListEqual<int>(L, copied);
    }
    return 0;
}
