// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

#include "checking_cycle.h"
#include "linked_list_prototype.h"

using std::cout;
using std::endl;
using std::make_shared;

void simple_test()
{
    shared_ptr<List_node<int>> L0 = make_shared<List_node<int>>(List_node<int>{42, nullptr});
    L0->next = L0;
    assert(has_cycle(L0));

    shared_ptr<List_node<int>> L1 = make_shared<List_node<int>>(List_node<int>{42, nullptr});
    shared_ptr<List_node<int>> L2 = make_shared<List_node<int>>(List_node<int>{42, nullptr});
    L1->next = L2;
    L2->next = L1;
    assert(has_cycle(L1) == L1);
    assert(has_cycle(L2) == L2);

    L2->next = nullptr;
    assert(has_cycle(L1) == nullptr);
    assert(has_cycle(L2) == nullptr);
}

int main(int argc, char* argv[])
{
    simple_test();
    shared_ptr<List_node<int>> L3 = make_shared<List_node<int>>(List_node<int>{3, nullptr});
    shared_ptr<List_node<int>> L2 = make_shared<List_node<int>>(List_node<int>{2, L3});
    shared_ptr<List_node<int>> L1 = make_shared<List_node<int>>(List_node<int>{1, L2});

    // Should output "L1 does not have cycle."
    assert(has_cycle(L1) == nullptr);
    cout << "L1 " << (has_cycle(L1) ? "has" : "does not have") << " cycle." << "\n";

    // Make it a cycle
    L3->next = L2;
    // Should output "L1 has cycle, located at node has value 2"
    assert(has_cycle(L1) != nullptr);
    assert(has_cycle(L1)->data == 2);
    auto temp = has_cycle(L1);
    if (temp) {
        cout << "L1 has cycle, located at node has value " << temp->data << "\n";
    } else {
        cout << "L1 does not have cycle" << "\n";
    }
    return 0;
}
