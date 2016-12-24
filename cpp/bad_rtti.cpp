#include <cstdlib>
#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;

//@include
class A {
public:
    virtual void foo() { cout << "A's foo" << "\n"; }
};

class B : public A {
public:
    void foo() override { cout << "B's foo" << "\n"; }

    virtual void bar() { cout << "B's bar" << "\n"; }
};

class C : public B {
public:
    void bar() override { cout << "C's bar" << "\n"; }

    void widget() { cout << "C's widget" << "\n"; }
};

void bad(A* x)
{
    if (typeid(*x) == typeid(A)) {
        x->foo();
    } else if (typeid(*x) == typeid(B)) {
        ((B*) x)->foo();
        ((B*) x)->bar();
    } else if (typeid(*x) == typeid(C)) {
        ((C*) x)->foo();
        ((C*) x)->bar();
        ((C*) x)->widget();
    }
}

//@exclude

A* random_builder()
{
    // int r = random()%3;
    int r = 2;
    if (r == 0) {
        return new A();
    } else if (r == 1) {
        cout << "returning a B" << "\n";
        return new B();
    } else if (r == 2) {
        return new C();
    } else {
        return new C();
    }
}

// @include
int main()
{
    // Randomly returns a pointer to  an A, B, or C type object.
    A* x = random_builder();
    bad(x);
}
// @exclude
