// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>

#include "doubly_linked_list_prototype.h"

template<typename Data_type>
std::shared_ptr<List_node<Data_type>> build_bst_from_sorted_doubly_linked_list_helper(std::shared_ptr<List_node<Data_type>>&, int, int);

// @include
// Returns the root of the corresponding BST. The prev and next fields of the
// list nodes are used as the BST nodes left and right fields, respectively.
// The length of the list is given.
template<typename Data_type>
std::shared_ptr<List_node<Data_type>> build_bst_from_sorted_doubly_linked_list(std::shared_ptr<List_node<Data_type>>& l, int length)
{
    return build_bst_from_sorted_doubly_linked_list_helper<Data_type>(l, 0, length);
}

// Builds a BST from the (start + 1)-th to the end-th node, inclusive, in L,
// and returns the root.
template<typename Data_type>
std::shared_ptr<List_node<Data_type>> build_bst_from_sorted_doubly_linked_list_helper(std::shared_ptr<List_node<Data_type>>& l_ref, int start, int end)
{
    if (start >= end) { return nullptr; }

    // int mid{start + ((end - start) / 2)};
    int mid{(start + end) / 2};
    auto left = build_bst_from_sorted_doubly_linked_list_helper<Data_type>(l_ref, start, mid);
    // The last function call sets L_ref to the successor of the maximum node in
    // the tree rooted at left.
    auto curr = l_ref;
    l_ref = (l_ref)->next;
    curr->prev = left;
    curr->next = build_bst_from_sorted_doubly_linked_list_helper<Data_type>(l_ref, mid + 1, end);
    return curr;
}
// @exclude

template<typename Data_type>
void inorder_traversal(const std::shared_ptr<List_node<Data_type>>& node, const Data_type& pre, int depth)
{
    if (node) {
        inorder_traversal(node->prev, pre, depth + 1);
        assert(pre <= node->data);
        std::cout << "List_node(" << node->data << ") " << "-> depth = " << depth << "\n";
        inorder_traversal(node->next, node->data, depth + 1);
    }
}

int main(int argc, char* argv[])
{
    auto temp0 = std::make_shared<List_node<int>>(List_node<int>{0});
    auto temp1 = std::make_shared<List_node<int>>(List_node<int>{1});
    auto temp2 = std::make_shared<List_node<int>>(List_node<int>{2});
    auto temp3 = std::make_shared<List_node<int>>(List_node<int>{3});
    temp0->next = temp1;
    temp1->next = temp2;
    temp2->next = temp3;
    temp3->next = nullptr;
    temp0->prev = nullptr;
    temp1->prev = temp0;
    temp2->prev = temp1;
    temp3->prev = temp2;

    auto l = temp0;
    auto tree = build_bst_from_sorted_doubly_linked_list(l, 4);
    inorder_traversal(tree, -1, 0);
    // Break the links of shared_ptr to prevent memory leak.
    temp1->prev = temp2->prev = temp3->prev = nullptr;
    return 0;
}
