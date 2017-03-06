// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <array>
#include <cassert>

using std::array;

// @include
int num_coins(int cents)
{
    const array<int, 6> coins{100, 50, 25, 10, 5, 1};
    auto n = 0;
    for (auto i = 0; i < coins.size(); ++i) {
        n += cents / coins[i];
        cents %= coins[i];
    }
    return n;
}
// @exclude

int main(int argc, char* argv[])
{
    assert(num_coins(100) == 1);
    assert(num_coins(101) == 2);
    assert(num_coins(68) == 6);
    assert(num_coins(13142) == 136);
    return 0;
}
