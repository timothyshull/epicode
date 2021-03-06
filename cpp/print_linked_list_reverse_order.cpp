// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <stack>

#include "linked_list_prototype.h"

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;
using std::stack;

// @include
void PrintLinkedListInReverse(shared_ptr<List_node<int>> head)
{
    stack<int> nodes;
    while (head) {
        nodes.push(head->data);
        head = head->next;
    }
    while (!nodes.empty()) {
        cout << nodes.top() << "\n";
        nodes.pop();
    }
}
// @exclude

int main(int argc, char* argv[])
{
    PrintLinkedListInReverse(make_shared<List_node<int>>(List_node<int>{
            1, make_shared<List_node<int>>(List_node<int>{
                    2, make_shared<List_node<int>>(List_node<int>{3, nullptr})})}));
    return 0;
}
