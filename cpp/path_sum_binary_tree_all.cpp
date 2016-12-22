// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

#include "binary_tree_prototype.h"

using std::cout;
using std::endl;
using std::make_unique;
using std::unique_ptr;
using std::vector;

void all_path_sum_helper(const unique_ptr<Binary_tree_node<int>>& root, int sum,
                         vector<int>* path, vector<vector<int>>* result);

// @include
vector<vector<int>> all_path_sum(const unique_ptr<Binary_tree_node<int>>& root,
                                 int sum)
{
    vector<int> path;
    vector<vector<int>> result;
    all_path_sum_helper(root, sum, &path, &result);
    return result;
}

void all_path_sum_helper(const unique_ptr<Binary_tree_node<int>>& root, int sum,
                         vector<int>* path, vector<vector<int>>* result)
{
    if (root) {
        path->emplace_back(root->data), sum -= root->data;
        if (!root->left && !root->right) {
            if (sum == 0) {
                result->emplace_back(*path);
            }
        } else {
            all_path_sum_helper(root->left, sum, path, result);
            all_path_sum_helper(root->right, sum, path, result);
        }
        path->pop_back();
    }
}
// @exclude

int main(int argc, char** argv)
{
    //      3
    //    2   5
    //  1    4 6
    unique_ptr<Binary_tree_node<int>> root = make_unique<Binary_tree_node<int>>(
            Binary_tree_node<int>{3, nullptr, nullptr});
    root->left = make_unique<Binary_tree_node<int>>(
            Binary_tree_node<int>{2, nullptr, nullptr});
    root->left->left = make_unique<Binary_tree_node<int>>(
            Binary_tree_node<int>{1, nullptr, nullptr});
    root->right = make_unique<Binary_tree_node<int>>(
            Binary_tree_node<int>{5, nullptr, nullptr});
    root->right->left = make_unique<Binary_tree_node<int>>(
            Binary_tree_node<int>{4, nullptr, nullptr});
    root->right->right = make_unique<Binary_tree_node<int>>(
            Binary_tree_node<int>{6, nullptr, nullptr});
    auto result = all_path_sum(root, 6);
    for (const vector<int>& a : result) {
        for (int v : a) {
            cout << v << " ";
        }
        cout << "\n";
    }
    return 0;
}
