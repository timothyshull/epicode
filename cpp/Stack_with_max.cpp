// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <stdexcept>

#include "./Stack_with_max.h"

using std::cout;
using std::endl;
using std::exception;

int main(int argc, char* argv[])
{
    Stack s;
    s.Push(1);
    s.Push(2);
    assert(s.Max() == 2);
    cout << s.Max() << "\n";  // 2
    cout << s.Pop() << "\n";  // 2
    assert(s.Max() == 1);
    cout << s.Max() << "\n";  // 1
    s.Push(3);
    s.Push(2);
    assert(s.Max() == 3);
    cout << s.Max() << "\n";  // 3
    s.Pop();
    assert(s.Max() == 3);
    cout << s.Max() << "\n";  // 3
    s.Pop();
    assert(s.Max() == 1);
    cout << s.Max() << "\n";  // 1
    s.Pop();
    try {
        s.Max();
        s.Pop();
        s.Pop();
        s.Pop();
        s.Pop();
    } catch (const exception& e) {
        cout << e.what() << "\n";
    }
    return 0;
}
