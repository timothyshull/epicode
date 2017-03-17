// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "binary_tree_prototype.h"
#include "binary_tree_utils.h"
#include "reconstruct_preorder_with_null.h"

using std::cout;
using std::default_random_engine;
using std::endl;
using std::make_unique;
using std::random_device;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;

template<typename T>
void GenPreorderWithNull(const unique_ptr<Binary_tree_node<T>>& n,
                         vector<T*>* p)
{
    if (!n) {
        p->emplace_back(nullptr);
        return;
    }

    p->emplace_back(&(n->data));
    GenPreorderWithNull(n->left, p);
    GenPreorderWithNull(n->right, p);
}

static void simple_test()
{
    int A[] = {1, 2, 3};
    vector<int*> preorder = {A, nullptr, nullptr};
    auto result = ReconstructPreorder(preorder);
    assert(result->data == 1);
    assert(result->left == nullptr);
    assert(result->right == nullptr);

    preorder = {A, nullptr, A + 1, nullptr, nullptr};
    result = ReconstructPreorder(preorder);
    assert(result->data == 1);
    assert(result->left == nullptr);
    assert(result->right->data == 2);

    preorder = {A, nullptr, A + 1, A + 2, nullptr, nullptr, nullptr};
    result = ReconstructPreorder(preorder);
    assert(result->data == 1);
    assert(result->left == nullptr);
    assert(result->right->data == 2);
    assert(result->right->left->data == 3);
    assert(result->right->right == nullptr);
}

int main(int argc, char* argv[])
{
    simple_test();
    default_random_engine gen((random_device()) ());
    // Random test 1000 times.
    for (int times = 0; times < 1000; ++times) {
        cout << times << "\n";
        int n;
        if (argc == 2) {
            n = atoi(argv[1]);
        } else {
            uniform_int_distribution<int> dis(1, 10000);
            n = dis(gen);
        }
        unique_ptr<Binary_tree_node<int>> root = generate_rand_binary_tree<int>(n);
        vector<int*> p;
        GenPreorderWithNull(root, &p);
        auto x = unique_ptr<Binary_tree_node<int>>(ReconstructPreorder(p));
        assert(is_two_binary_trees_equal(root, x));
    }
    return 0;
}
