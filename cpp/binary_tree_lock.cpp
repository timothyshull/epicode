// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

using std::boolalpha;
using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

// @include
class Binary_tree_node {
public:
    bool is_locked() const { return locked_; }

    bool lock()
    {
        // We cannot lock if any of this node's descendants are locked.
        if (num_locked_descendants_ > 0 || locked_) {
            return false;
        }

        // We cannot lock if any of this node's ancestors are locked.
        for (auto iter = parent_; iter != nullptr; iter = iter->parent_) {
            if (iter->locked_) {
                return false;
            }
        }

        // lock this node and increments all its ancestors's descendant lock
        // counts.
        locked_ = true;
        for (auto iter = parent_; iter != nullptr; iter = iter->parent_) {
            ++iter->num_locked_descendants_;
        }
        return true;
    }

    void unlock()
    {
        if (locked_) {
            // Unlocks itself and decrements its ancestors's descendant lock counts.
            locked_ = false;
            for (auto iter = parent_; iter != nullptr; iter = iter->parent_) {
                --iter->num_locked_descendants_;
            }
        }
    }

    // @exclude
    shared_ptr<Binary_tree_node>& left() { return left_; }

    shared_ptr<Binary_tree_node>& right() { return right_; }

    shared_ptr<Binary_tree_node>& parent() { return parent_; }
    // @include
private:
    shared_ptr<Binary_tree_node> left_, right_, parent_;

    bool locked_ = false;
    int num_locked_descendants_ = 0;
};
// @exclude

int main(int argc, char* argv[])
{
    auto root = make_shared<Binary_tree_node>(Binary_tree_node());
    root->left() = make_shared<Binary_tree_node>(Binary_tree_node());
    root->left()->parent() = root;
    root->right() = make_shared<Binary_tree_node>(Binary_tree_node());
    root->right()->parent() = root;
    root->left()->left() = make_shared<Binary_tree_node>(Binary_tree_node());
    root->left()->left()->parent() = root->left();
    root->left()->right() = make_shared<Binary_tree_node>(Binary_tree_node());
    root->left()->right()->parent() = root->left();

    assert(!root->is_locked());
    cout << boolalpha << root->is_locked() << "\n";

    assert(root->lock());
    assert(root->is_locked());
    cout << boolalpha << root->is_locked() << "\n";
    assert(!root->left()->lock());
    assert(!root->left()->is_locked());
    assert(!root->right()->lock());
    assert(!root->right()->is_locked());
    assert(!root->left()->left()->lock());
    assert(!root->left()->left()->is_locked());
    assert(!root->left()->right()->lock());
    assert(!root->left()->right()->is_locked());

    root->unlock();
    assert(root->left()->lock());
    assert(!root->lock());
    assert(!root->left()->left()->lock());
    assert(!root->is_locked());

    cout << boolalpha << root->is_locked() << "\n";
    assert(root->right()->lock());
    assert(root->right()->is_locked());
    cout << boolalpha << root->right()->is_locked() << "\n";
    return 0;
}
