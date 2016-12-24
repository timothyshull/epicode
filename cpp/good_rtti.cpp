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

class D : public B {
public:
    void bar() override { cout << "D's bar" << "\n"; }
};

//@include
void good(A* x)
{
    x->foo();
    // Objects of type D can be cast to a B, so the call below is to D's bar().
    B* p = dynamic_cast<B*>(x);
    if (p) {
        p->bar();
    }
    C* q = dynamic_cast<C*>(x);
    if (q) {
        q->widget();
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
    /*
    ...
    */
    // Randomly returns a pointer to  an A, B, or C type object.
    A* x = random_builder();
    good(x);
}
