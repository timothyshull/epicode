#include <iostream>

using namespace std;

struct Binary_tree {
    int data;
    Binary_tree* left, * right;

    Binary_tree(int val = 0, Binary_tree* l = nullptr, Binary_tree* r = nullptr)
            : data(val), left(l), right(r) {}
};

// @include
Binary_tree* convert_tree_to_doubly_list(Binary_tree* n)
{
    if (n == nullptr) {
        return nullptr;
    }

    Binary_tree* L = convert_tree_to_doubly_list(n->left);
    Binary_tree* R = convert_tree_to_doubly_list(n->right);
    // Join L and n as a doubly linked list
    Binary_tree* L_tail = nullptr;
    if (L) {
        L_tail = L->left;
        L_tail->right = n, n->left = L_tail;
        L_tail = n;
    } else {
        L = L_tail = n;
    }

    // Join L and R as a doubly linked list
    Binary_tree* R_tail = nullptr;
    if (R) {
        R_tail = R->left;
        L_tail->right = R, R->left = L_tail;
    } else {
        R_tail = L_tail;
    }
    R_tail->right = L, L->left = R_tail;
    return L;
}
// @exclude

int main(int argc, char* argv[])
{
    //      3
    //    2   5
    //  1    4 6
    Binary_tree* root = new Binary_tree(3);
    root->left = new Binary_tree(2);
    root->left->left = new Binary_tree(1);
    root->right = new Binary_tree(5);
    root->right->left = new Binary_tree(4);
    root->right->right = new Binary_tree(6);
    // should output 1, 2, 3, 4, 5, 6
    Binary_tree* head = convert_tree_to_doubly_list(root);
    Binary_tree* temp = head;
    do {
        cout << temp->data << "\n";
        temp = temp->right;
    } while (temp != head);
    return 0;
}
