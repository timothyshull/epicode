// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <stack>
#include <stdexcept>

using std::cout;
using std::endl;
using std::exception;
using std::length_error;
using std::numeric_limits;
using std::stack;

// @include
class Queue {
public:
    void enqueue(int x) { enq_.emplace(x); }

    int dequeue()
    {
        if (deq_.empty()) {
            // Transfers the elements in enq_ to deq_.
            while (!enq_.empty()) {
                deq_.emplace(enq_.top());
                enq_.pop();
            }
        }

        if (deq_.empty()) {  // deq_ is still empty!
            throw length_error("empty queue");
        }
        int ret = deq_.top();
        deq_.pop();
        return ret;
    }

private:
    stack<int> enq_, deq_;
};
// @exclude

int main(int argc, char* argv[])
{
    Queue Q;
    Q.enqueue(1);
    Q.enqueue(2);
    assert(1 == Q.dequeue());
    assert(2 == Q.dequeue());
    Q.enqueue(3);
    assert(3 == Q.dequeue());
    try {
        Q.dequeue();
        assert(false);
    } catch (const exception& e) {
        cout << e.what() << "\n";
    }
    Q.enqueue(-1);
    Q.enqueue(123);
    Q.enqueue(numeric_limits<int>::max());
    Q.enqueue(numeric_limits<int>::min());
    Q.enqueue(0);
    assert(-1 == Q.dequeue());
    Q.enqueue(0);
    assert(123 == Q.dequeue());
    assert(numeric_limits<int>::max() == Q.dequeue());
    assert(numeric_limits<int>::min() == Q.dequeue());
    assert(0 == Q.dequeue());
    assert(0 == Q.dequeue());
    try {
        Q.dequeue();
        assert(false);
    } catch (const exception& e) {
        cout << e.what() << "\n";
    }
    return 0;
}
