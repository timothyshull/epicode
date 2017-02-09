#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

// @include
bool two_difference(const std::vector<int>& coll, int k)
{
    auto i = coll.size() - 1;
    auto j = coll.size() - 1;
    while (i >= 0 && j >= 0) {
        if (coll[i] - coll[j] == k) {
            std::cout << coll[i] << ' ' << coll[j] << ' ' << k << "\n";
            return true;
        } else if (coll[i] - coll[j] > k) {
            --i;
        } else {
            --j;
        }
    }
    return false;
}
// @exclude

// n^2 solution
bool check_ans(const std::vector<int>& coll, int k)
{
    for (int i{0}; i < coll.size(); ++i) {
        for (int j = 0; j < coll.size(); ++j) {
            if (coll[i] - coll[j] == k) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
    // TODO: fix use of C-style random here
    int n;
    int k;
    std::srand(static_cast<unsigned>(time(nullptr)));
    if (argc == 2) {
        n = std::stoi(argv[1]);
        k = std::rand() % n;
    } else if (argc == 3) {
        n = std::stoi(argv[1]);
        k = std::stoi(argv[2]);
    } else {
        n = 1 + std::rand() % 10000;
        k = std::rand() % n;
    }
    std::vector<int> coll;
    for (size_t i = 0; i < n; ++i) {
        coll.push_back(((rand() & 1) ? -1 : 1) * rand() % 100000);
    }
    sort(coll.begin(), coll.end());
    for (int i = 0; i < coll.size(); ++i) {
        std::cout << coll[i] << ' ';
    }
    std::cout << "\n";
    std::cout << std::boolalpha << two_difference(coll, k) << "\n";
    assert(check_ans(coll, k) == two_difference(coll, k));
    return 0;
}
