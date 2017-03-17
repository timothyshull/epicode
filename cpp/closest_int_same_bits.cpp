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

// @include
unsigned long closest_int_same_bit_count(unsigned long x)
{
    const static int kNumUnsignedBits = 64;
    for (int i = 0; i < kNumUnsignedBits - 1; ++i) {
        if (((x >> i) & 1) != ((x >> (i + 1)) & 1)) {
            x ^= (1UL << i) | (1UL << (i + 1));  // Swaps bit-i and bit-(i + 1).
            return x;
        }
    }

    // Throw error if all bits of x are 0 or 1.
    throw invalid_argument("All bits are 0 or 1");
}
// @exclude

int count_bits_set_to_1(unsigned long x)
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
    assert(closest_int_same_bit_count(numeric_limits<unsigned long>::max() - 1) == numeric_limits<unsigned long>::max() - 2);

    try {
        closest_int_same_bit_count(numeric_limits<unsigned long>::max());
        assert(false);
    } catch (const exception& e) {
        cout << e.what() << "\n";
    }
    try {
        closest_int_same_bit_count(0);
        assert(false);
    } catch (const exception& e) {
        cout << e.what() << "\n";
    }
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
        uniform_int_distribution<int> dis(0, numeric_limits<unsigned long>::max());
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
