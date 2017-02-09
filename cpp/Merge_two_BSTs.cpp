// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <memory>

#include "bst_prototype_shared_ptr.h"

using std::cout;
using std::endl;
using std::make_shared;
using std::numeric_limits;
using std::shared_ptr;

shared_ptr<BST_node<int>> BSTToDoublyListHelper(
        const shared_ptr<BST_node<int>>&);

shared_ptr<BST_node<int>> MergeTwoSortedLists(shared_ptr<BST_node<int>>,
                                              shared_ptr<BST_node<int>>);

void AppendNode(shared_ptr<BST_node<int>>*, shared_ptr<BST_node<int>>*);

// Build a BST from the (s + 1)-th to the e-th node in L.
shared_ptr<BST_node<int>> BuildBSTFromSortedDoublyListHelper(
        shared_ptr<BST_node<int>>* L, int s, int e)
{
    shared_ptr<BST_node<int>> curr = nullptr;
    if (s < e) {
        int m = s + ((e - s) / 2);
        auto temp = BuildBSTFromSortedDoublyListHelper(L, s, m);
        curr = *L;
        curr->left = temp;
        *L = (*L)->right;
        curr->right = BuildBSTFromSortedDoublyListHelper(L, m + 1, e);
    }
    return curr;
}

shared_ptr<BST_node<int>> BuildBSTFromSortedDoublyList(
        shared_ptr<BST_node<int>> L, int n)
{
    return BuildBSTFromSortedDoublyListHelper(&L, 0, n);
}

shared_ptr<BST_node<int>> BSTToDoublyList(const shared_ptr<BST_node<int>>& n)
{
    auto res = BSTToDoublyListHelper(n);
    res->left->right = nullptr;  // breaks the link from tail to head.
    res->left = nullptr;  // breaks the link from head to tail.
    return res;
}

// Transform a BST into a circular sorted doubly linked list in-place,
// return the head of the list.
shared_ptr<BST_node<int>> BSTToDoublyListHelper(
        const shared_ptr<BST_node<int>>& n)
{
    // Empty subtree.
    if (!n) {
        return nullptr;
    }

    // Recursively build the list from left and right subtrees.
    auto l_head(BSTToDoublyListHelper(n->left)),
            r_head(BSTToDoublyListHelper(n->right));

    // Append n to the list from left subtree.
    shared_ptr<BST_node<int>> l_tail = nullptr;
    if (l_head) {
        l_tail = l_head->left;
        l_tail->right = n;
        n->left = l_tail;
        l_tail = n;
    } else {
        l_head = l_tail = n;
    }

    // Append the list from right subtree to n.
    shared_ptr<BST_node<int>> r_tail = nullptr;
    if (r_head) {
        r_tail = r_head->left;
        l_tail->right = r_head;
        r_head->left = l_tail;
    } else {
        r_tail = l_tail;
    }
    r_tail->right = l_head, l_head->left = r_tail;

    return l_head;
}

// Count the list length till end.
int CountLength(shared_ptr<BST_node<int>> L)
{
    int len = 0;
    while (L) {
        ++len, L = L->right;
    }
    return len;
}

// @include
shared_ptr<BST_node<int>> MergeTwoBSTs(shared_ptr<BST_node<int>> A,
                                       shared_ptr<BST_node<int>> B)
{
    A = BSTToDoublyList(A), B = BSTToDoublyList(B);
    int A_length = CountLength(A), B_length = CountLength(B);
    return BuildBSTFromSortedDoublyList(MergeTwoSortedLists(A, B),
                                        A_length + B_length);
}
// @exclude

// Merges two sorted doubly linked lists, returns the head of merged list.
shared_ptr<BST_node<int>> MergeTwoSortedLists(shared_ptr<BST_node<int>> A,
                                              shared_ptr<BST_node<int>> B)
{
    shared_ptr<BST_node<int>> sorted_head(new BST_node<int>);
    shared_ptr<BST_node<int>> tail = sorted_head;

    while (A && B) {
        AppendNode(A->data < B->data ? &A : &B, &tail);
    }

    if (A) {
        // Appends the remaining of A.
        AppendNode(&A, &tail);
    } else if (B) {
        // Appends the remaining of B.
        AppendNode(&B, &tail);
    }
    return sorted_head->right;
}

void AppendNode(shared_ptr<BST_node<int>>* node,
                shared_ptr<BST_node<int>>* tail)
{
    (*tail)->right = *node;
    *tail = *node;  // Resets tail to the last node.
    *node = (*node)->right;
}

template<typename T>
void PrintBSTInorder(shared_ptr<BST_node<T>> n, const T& pre)
{
    if (n) {
        PrintBSTInorder(n->left, pre);
        assert(pre <= n->data);
        cout << n->data << ' ';
        PrintBSTInorder(n->right, n->data);
    }
}

int main(int argc, char* argv[])
{
    //      3
    //    2   5
    //  1    4 6
    auto L = make_shared<BST_node<int>>(BST_node<int>{3});
    L->left = make_shared<BST_node<int>>(BST_node<int>{2});
    L->left->left = make_shared<BST_node<int>>(BST_node<int>{1});
    L->right = make_shared<BST_node<int>>(BST_node<int>{5});
    L->right->left = make_shared<BST_node<int>>(BST_node<int>{4});
    L->right->right = make_shared<BST_node<int>>(BST_node<int>{6});
    //     7
    //   2   8
    // 0
    auto R = make_shared<BST_node<int>>(BST_node<int>{7});
    R->left = make_shared<BST_node<int>>(BST_node<int>{2});
    R->left->left = make_shared<BST_node<int>>(BST_node<int>{0});
    R->right = make_shared<BST_node<int>>(BST_node<int>{8});
    shared_ptr<BST_node<int>> root = MergeTwoBSTs(L, R);
    // should output 0 1 2 2 3 4 5 6 7 8
    PrintBSTInorder(root, numeric_limits<int>::min());
    return 0;
}
