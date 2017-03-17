// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>

#include "Lru_cache.h"

int main(int argc, char* argv[])
{
    const int kCapacity = 2;
    {
        Lru_cache<kCapacity> c;
        std::cout << "c.insert(1, 1)" << "\n";
        c.insert(1, 1);
        std::cout << "c.insert(1, 10)" << "\n";
        c.insert(1, 10);
        int val;
        std::cout << "c.lookup(2, val)" << "\n";
        assert(!c.lookup(2, val));
        std::cout << "c.lookup(1, val)" << "\n";
        assert(c.lookup(1, val));
        assert(val == 1);
        c.erase(1);
        assert(!c.lookup(1, val));
    }

    // test capacity constraints honored, also FIFO ordering
    {
        Lru_cache<kCapacity> c;
        c.insert(1, 1);
        c.insert(2, 1);
        c.insert(3, 1);
        c.insert(4, 1);
        int val;
        assert(!c.lookup(1, val));
        assert(!c.lookup(2, val));
        assert(c.lookup(3, val));
        assert(val == 1);
        assert(c.lookup(4, val));
        assert(val == 1);
    }

    // test retrieval moves to front
    {
        Lru_cache<kCapacity> c;
        c.insert(1, 1);
        c.insert(2, 1);
        c.insert(3, 1);
        int val;
        c.lookup(2, val);
        c.insert(4, 1);
        assert(!c.lookup(1, val));
        assert(c.lookup(2, val));
        assert(val == 1);
        assert(!c.lookup(3, val));
        assert(c.lookup(4, val));
        assert(val == 1);
    }

    // test update moves to front
    {
        Lru_cache<kCapacity> c;
        c.insert(1, 1);
        c.insert(2, 1);
        c.insert(3, 1);
        c.insert(2, 2);
        c.insert(4, 1);
        int val;
        assert(!c.lookup(1, val));
        assert(c.lookup(2, val));
        assert(val == 1);
        assert(!c.lookup(3, val));
        assert(c.lookup(4, val));
        assert(val == 1);
    }

    // test remove
    {
        Lru_cache<kCapacity> c;
        c.insert(1, 1);
        c.insert(2, 1);
        c.erase(2);
        c.insert(3, 3);
        int val;
        assert(c.lookup(1, val));
        assert(val == 1);
        assert(!c.lookup(2, val));
        assert(c.lookup(3, val));
        assert(val == 3);
    }
    return 0;
}
