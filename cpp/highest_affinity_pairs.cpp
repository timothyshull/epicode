// Copyright (c) 2016 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::pair;
using std::random_device;
using std::set;
using std::stoi;
using std::string;
using std::uniform_int_distribution;
using std::unordered_map;
using std::vector;

// @include
struct PagePair {
    string page_a, page_b;
};

PagePair HighestAffinityPair(ifstream* ifs)
{
    // Creates a mapping from pages to distinct users.
    unordered_map<string, set<string>> page_users_map;
    string page, user;
    while (*ifs >> page >> user) {
        page_users_map[page].emplace(user);
    }

    PagePair result;
    int max_count = 0;
    // Compares all pairs of pages to users maps.
    for (auto a = page_users_map.begin(); a != page_users_map.end(); ++a) {
        auto b = a;
        for (advance(b, 1); b != page_users_map.end(); ++b) {
            vector<string> intersect_users;
            set_intersection(a->second.begin(), a->second.end(), b->second.begin(),
                             b->second.end(), back_inserter(intersect_users));

            // Updates result if we find larger intersection.
            if (intersect_users.size() > max_count) {
                max_count = intersect_users.size();
                result = {a->first, b->first};
            }
        }
    }
    return result;
}
// @exclude

string rand_string(int len)
{
    default_random_engine gen((random_device()) ());
    uniform_int_distribution<int> dis('a', 'z');
    string ret;
    while (len--) {
        ret += dis(gen);
    }
    return ret;
}

void simple_test()
{
    ofstream ofs("/tmp/logs.txt");
    ofs << "a A" << "\n";
    ofs << "b B" << "\n";
    ofs << "c A" << "\n";
    ofs.close();
    ifstream ifs("/tmp/logs.txt");
    auto result = HighestAffinityPair(&ifs);
    assert((result.page_a == "a" && result.page_b == "c") ||
           (result.page_a == "c" && result.page_b == "a"));
}

int main(int argc, char* argv[])
{
    simple_test();
    default_random_engine gen((random_device()) ());
    int n;
    if (argc == 2) {
        n = stoi(argv[1]);
    } else {
        uniform_int_distribution<int> dis(1, 10000);
        n = dis(gen);
    }
    ofstream ofs("/tmp/logs.txt");
    for (int i = 0; i < n; ++i) {
        string name = rand_string(5);
        transform(name.begin(), name.end(), name.begin(), toupper);
        ofs << name << " " << rand_string(5) << "\n";
    }
    ofs.close();
    ifstream ifs("/tmp/logs.txt");
    auto result = HighestAffinityPair(&ifs);
    cout << result.page_a << " " << result.page_b << "\n";
    return 0;
}
