// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

#include "linked_list_prototype.h"
#include "reverse_linked_list_iterative.h"

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

template<typename T>
void Print(shared_ptr<List_node<T>> head)
{
    if (head) {
        cout << "(" << head->data << ")" << "\n";
        Print(head->next);
    }
}

int main(int argc, char* argv[])
{
    shared_ptr<List_node<int>> L1 =
            make_shared<List_node<int>>(List_node<int>{1, nullptr});
    shared_ptr<List_node<int>> L2 =
            make_shared<List_node<int>>(List_node<int>{2, nullptr});
    L1->next = L2;
    shared_ptr<List_node<int>> L3 =
            make_shared<List_node<int>>(List_node<int>{3, nullptr});
    L2->next = L3;

    cout << "before reverse" << "\n";
    Print(L1);
    shared_ptr<List_node<int>> newhead = ReverseLinkedList(L1);
    cout << "\n" << "after reverse" << "\n";
    assert(newhead->data == 3 && newhead->next->data == 2 &&
           newhead->next->next->data == 1);
    Print(newhead);
    newhead = ReverseLinkedList(newhead);
    assert(newhead->data == 1 && newhead->next->data == 2 &&
           newhead->next->next->data == 3);
    cout << "\n" << "after another reverse" << "\n";
    Print(newhead);
    return 0;
}
