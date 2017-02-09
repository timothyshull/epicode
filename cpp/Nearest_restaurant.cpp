// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <memory>
#include <vector>

#include "bst_parent_prototype.h"

using std::make_unique;
using std::unique_ptr;
using std::vector;

BST_node<int>* FindSuccessorBST(BST_node<int>* n)
{
    if (n->right) {
        // Find the smallest element in n's right subtree.
        n = n->right.get();
        while (n->left) {
            n = n->left.get();
        }
        return n;
    }

    // Find the first parent which is larger than n.
    while (n->parent && n->parent->right.get() == n) {
        n = n->parent;
    }
    // Return nullptr means n is the largest in this BST.
    return n->parent ? n->parent : nullptr;
}

BST_node<int>* FindFirstLargerEqualK(const unique_ptr<BST_node < int>>

& r,

int k

);

// @include
vector<BST_node < int>*>

RangeQueryOnBST(const unique_ptr<BST_node < int>>

& n,

int L,

int U

)
{
vector<BST_node < int>*>

res;

for (

auto* it = FindFirstLargerEqualK(n, L);

it&& it

->data <=

U;

it = FindSuccessorBST(it)

) {
res.

emplace_back(it);

}
return

res;

}

BST_node<int>* FindFirstLargerEqualK(const unique_ptr<BST_node < int>>

& r,

int k

)
{
if (!r) {
return nullptr;
} else if (r->data<k) {
// r->data < k so search the right subtree.
return

FindFirstLargerEqualK(r

->right, k);
}

// Recursively search the left subtree for first one >= k.
auto n = FindFirstLargerEqualK(r->left, k);

return n ?

n : r

.

get();

}
// @exclude

int main(int argc, char* argv[])
{
    //      3
    //    2   5
    //  1    4  6
    auto root = make_unique<BST_node < int>>
    (BST_node < int > {3});
    root->parent = nullptr;
    root->left = make_unique<BST_node < int>>
    (BST_node < int > {2});
    root->left->parent = root.get();
    root->left->left = make_unique<BST_node < int>>
    (BST_node < int > {1});
    root->left->left->parent = root->left.get();
    root->right = make_unique<BST_node < int>>
    (BST_node < int > {5});
    root->right->parent = root.get();
    root->right->left = make_unique<BST_node < int>>
    (BST_node < int > {4});
    root->right->left->parent = root->right.get();
    root->right->right = make_unique<BST_node < int>>
    (BST_node < int > {6});
    root->right->right->parent = root->right.get();
    vector<BST_node < int>*> res = RangeQueryOnBST(root, 2, 5);
    assert(res.size() == 4);
    for (const auto* l : res) {
        assert(l->data >= 2 && l->data <= 5);
    }
    res = RangeQueryOnBST(root, -1, 0);
    assert(res.empty());
    res = RangeQueryOnBST(root, 10, 25);
    assert(res.empty());
    res = RangeQueryOnBST(root, -10, 30);
    assert(res.size() == 6);
    for (const auto* l : res) {
        assert(l->data >= 1 && l->data <= 6);
    }
    return 0;
}
