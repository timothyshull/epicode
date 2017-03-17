// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <random>

#include "bst_prototype.h"

std::unique_ptr<BST_node<int>> build_min_height_bst_from_sorted_array_helper(const std::vector<int>&, int, int);

// @include
std::unique_ptr<BST_node<int>> build_min_height_bst_from_sorted_array(const std::vector<int>& a)
{
    return build_min_height_bst_from_sorted_array_helper(a, 0, static_cast<int>(a.size())); // narrow_cast
}

// Build a min-height BST over the entries in A[start : end - 1].
std::unique_ptr<BST_node<int>> build_min_height_bst_from_sorted_array_helper(const std::vector<int>& a, int start, int end)
{
    if (start >= end) { return nullptr; }
    int mid{start + ((end - start) / 2)};
    return std::make_unique<BST_node<int>>(BST_node<int>{a[mid], build_min_height_bst_from_sorted_array_helper(a, start, mid), build_min_height_bst_from_sorted_array_helper(a, mid + 1, end)});
}
// @exclude

template<typename Data_type>
void traversal_check(const std::unique_ptr<BST_node<Data_type>>& tree, Data_type& target)
{
    if (tree) {
        traversal_check(tree->left, target);
        assert(tree->data == target);
        ++target;
        traversal_check(tree->right, target);
    }
}

static void simple_test()
{
    std::vector<int> a{1, 2, 3, 4};
    std::unique_ptr<BST_node<int>> result{build_min_height_bst_from_sorted_array(a)};
    assert(3 == result->data);
    assert(2 == result->left->data);
    assert(1 == result->left->left->data);
    assert(4 == result->right->data);
}

int main(int argc, char* argv[])
{
    simple_test();
    std::random_device rd;
    std::default_random_engine gen{rd()};
    int n = (argc == 2) ? std::stoi(argv[1]) : 0;
    std::uniform_int_distribution<int> dis{1, 1000};
    for (int times{0}; times < 1000; ++times) {
        if (argc != 2) { n = dis(gen); }
        std::vector<int> a(static_cast<std::vector<int>::size_type>(n));
        std::iota(a.begin(), a.end(), 0);
        std::unique_ptr<BST_node<int>> tree{build_min_height_bst_from_sorted_array(a)};
        int target{0};
        traversal_check<int>(tree, target);
    }
    return 0;
}
