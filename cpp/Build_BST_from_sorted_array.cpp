// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "bst_prototype.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::make_unique;
using std::random_device;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;

unique_ptr<BST_node<int>> build_min_height_bst_from_sorted_array_helper(const vector<int>&, int, int);

// @include
unique_ptr<BST_node<int>> build_min_height_bst_from_sorted_array(const vector<int>& A)
{
    return build_min_height_bst_from_sorted_array_helper(A, 0, A.size());
}

// Build a min-height BST over the entries in A[start : end - 1].
unique_ptr<BST_node<int>> build_min_height_bst_from_sorted_array_helper(
        const vector<int>& A, int start, int end)
{
    if (start >= end) {
        return nullptr;
    }
    int mid = start + ((end - start) / 2);
    return make_unique<BST_node<int>>(BST_node<int>{
            A[mid], build_min_height_bst_from_sorted_array_helper(A, start, mid),
            build_min_height_bst_from_sorted_array_helper(A, mid + 1, end)});
}
// @exclude

template<typename T>
void TraversalCheck(const unique_ptr<BST_node<T>>& tree, T* target)
{
    if (tree) {
        TraversalCheck(tree->left, target);
        assert(*target == tree->data);
        ++*target;
        TraversalCheck(tree->right, target);
    }
}

static void simple_test()
{
    vector<int> A = {1, 2, 3, 4};
    unique_ptr<BST_node<int>> result = build_min_height_bst_from_sorted_array(A);
    assert(3 == result->data);
    assert(2 == result->left->data);
    assert(1 == result->left->left->data);
    assert(4 == result->right->data);
}

int main(int argc, char* argv[])
{
    simple_test();
    random_device rd;
    default_random_engine gen(rd());
    for (int times = 0; times < 1000; ++times) {
        int n;
        if (argc == 2) {
            n = atoi(argv[1]);
        } else {
            uniform_int_distribution<int> dis(1, 1000);
            n = dis(gen);
        }
        vector<int> A(n);
        iota(A.begin(), A.end(), 0);
        unique_ptr<BST_node<int>> tree = build_min_height_bst_from_sorted_array(A);
        int target = 0;
        TraversalCheck<int>(tree, &target);
    }
    return 0;
}
