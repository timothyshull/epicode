#include <cstdlib>
#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;

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

//@include
class D : public B {
public:
    void bar() override { cout << "D's bar" << "\n"; }
};

void bad(A* x)
{
    if (typeid(*x) == typeid(A)) {
        x->foo();
    } else if (typeid(*x) == typeid(B) || typeid(*x) == typeid(D)) {
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
    int r = 3;
    if (r == 0) {
        return new A();
    } else if (r == 1) {
        cout << "returning a B" << "\n";
        return new B();
    } else if (r == 2) {
        return new C();
    } else {
        return new D();
    }
}

int main(int argc, char** argv)
{
    // Randomly returns a pointer to  an A, B, or C type object.
    A* x = random_builder();
    bad(x);
}
