// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::exception;
using std::invalid_argument;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;

unsigned long lowest_set_bit(unsigned long);

unsigned long lowest_unset_bit(unsigned long);

// @include
unsigned long closest_int_same_bit_count(unsigned long x)
{
    if (x == 0 || x == numeric_limits<unsigned long>::max()) {
        throw invalid_argument("All bits are 0 or 1");
    }
    unsigned long mask = (x & 1) == 0 ? lowest_set_bit(x) : lowest_unset_bit(x);
    mask = mask | (mask >> 1);
    return x ^ mask;
}

unsigned long lowest_set_bit(unsigned long x) { return x & ~(x - 1); }

unsigned long lowest_unset_bit(unsigned long x) { return lowest_set_bit(x + 1); }
// @exclude

int count_bits_set_to_1(int x)
{
    int count = 0;
    while (x) {
        x &= (x - 1);
        ++count;
    }
    return count;
}

void small_test()
{
    assert(closest_int_same_bit_count(6) == 5);
    assert(closest_int_same_bit_count(7) == 11);
    assert(closest_int_same_bit_count(2) == 1);
    assert(closest_int_same_bit_count(32) == 16);
}

int main(int argc, char* argv[])
{
    small_test();
    random_device rd;
    default_random_engine gen(rd());
    unsigned long x;
    if (argc == 2) {
        x = atol(argv[1]);
    } else {
        uniform_int_distribution<int> dis(0, numeric_limits<int>::max());
        x = dis(gen);
    }
    try {
        unsigned long res = closest_int_same_bit_count(x);
        cout << x << ' ' << res << "\n";
        assert(count_bits_set_to_1(x) == count_bits_set_to_1(res));
    } catch (const exception& e) {
        cout << x << ' ' << e.what() << "\n";
    }
    return 0;
}
