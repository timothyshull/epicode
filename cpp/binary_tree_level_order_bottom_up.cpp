// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

#include "binary_tree_prototype.h"

using std::cout;
using std::endl;
using std::make_unique;
using std::queue;
using std::unique_ptr;
using std::vector;

// @include
vector<vector<int>> zigzag_level_order(
        const unique_ptr<Binary_tree_node<int>>& root)
{
    vector<vector<int>> res;
    vector<int> one_level;
    queue<Binary_tree_node<int>*> curr_level, next_level;
    curr_level.emplace(root.get());
    while (!curr_level.empty()) {
        auto curr_node = curr_level.front();
        curr_level.pop();
        if (curr_node) {
            one_level.emplace_back(curr_node->data);
            next_level.emplace(curr_node->left.get());
            next_level.emplace(curr_node->right.get());
        }
        if (curr_level.empty() && !one_level.empty()) {
            res.emplace_back(move(one_level));
            curr_level.swap(next_level);
        }
    }
    reverse(res.begin(), res.end());
    return res;
}
// @exclude

int main(int argc, char* argv[])
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
    auto res = zigzag_level_order(root);
    vector<vector<int>> golden_res = {{1, 4, 6},
                                      {2, 5},
                                      {3}};
    assert(golden_res.size() == res.size());
    for (size_t i = 0; i < res.size(); ++i) {
        assert(res[i].size() == golden_res[i].size());
        for (size_t j = 0; j < res[i].size(); ++j) {
            assert(res[i][j] == golden_res[i][j]);
            cout << res[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
