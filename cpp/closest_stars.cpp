// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <queue>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using std::array;
using std::cout;
using std::default_random_engine;
using std::endl;
using std::istringstream;
using std::max;
using std::min;
using std::priority_queue;
using std::random_device;
using std::stoi;
using std::string;
using std::stringstream;
using std::swap;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::vector;

// @include
struct Star {
    bool operator<(const Star& that) const
    {
        return distance() < that.distance();
    }

    double distance() const { return sqrt(x * x + y * y + z * z); }

    double x, y, z;
};

vector<Star> find_closest_k_stars(int k, istringstream* stars)
{
    // max_heap to store the closest k stars seen so far.
    priority_queue<Star, vector<Star>> max_heap;

    string line;
    while (getline(*stars, line)) {
        stringstream line_stream(line);
        array<double, 3> data;  // stores x, y, and z.
        for (int i = 0; i < 3; ++i) {
            string buf;
            getline(line_stream, buf, ',');
            data[i] = stod(buf);
        }

        // Add each star to the max-heap. If the max-heap size exceeds k,
        // remove the maximum element from the max-heap.
        max_heap.emplace(Star{data[0], data[1], data[2]});
        if (max_heap.size() == k + 1) {
            max_heap.pop();
        }
    }

    // Iteratively extract from the max-heap, which yields the stars
    // sorted according from furthest to closest.
    vector<Star> closest_stars;
    while (!max_heap.empty()) {
        closest_stars.emplace_back(max_heap.top());
        max_heap.pop();
    }
    return vector<Star>(closest_stars.rbegin(), closest_stars.rend());
}
// @exclude

string CreateStreamingString(const vector<Star>& stars)
{
    string s;
    for (int i = 0; i < stars.size(); ++i) {
        stringstream ss;
        ss << stars[i].x << ',' << stars[i].y << ',' << stars[i].z << "\n";
        s += ss.str();
    }
    return s;
}

void simple_test()
{
    vector<Star> stars;
    stars.emplace_back((Star{1, 2, 3}));
    stars.emplace_back((Star{5, 5, 5}));
    stars.emplace_back((Star{0, 2, 1}));
    stars.emplace_back((Star{9, 2, 1}));
    stars.emplace_back((Star{1, 2, 1}));
    stars.emplace_back((Star{2, 2, 1}));
    istringstream sin(CreateStreamingString(stars));
    vector<Star> closest_stars = find_closest_k_stars(3, &sin);
    assert(3 == closest_stars.size());
    assert(closest_stars[0].distance() == (Star{0, 2, 1}.distance()));
    assert(closest_stars[0].distance() == (Star{2, 0, 1}.distance()));
    assert(closest_stars[1].distance() == (Star{1, 2, 1}.distance()));
    assert(closest_stars[1].distance() == (Star{1, 1, 2}.distance()));

    stars.clear();
    stars.emplace_back((Star{1, 2, 3}));
    stars.emplace_back((Star{5, 5, 5}));
    stars.emplace_back((Star{4, 4, 4}));
    stars.emplace_back((Star{3, 2, 1}));
    stars.emplace_back((Star{5, 5, 5}));
    stars.emplace_back((Star{3, 2, 3}));
    stars.emplace_back((Star{3, 2, 3}));
    stars.emplace_back((Star{3, 2, 1}));
    istringstream sin2(CreateStreamingString(stars));
    closest_stars = find_closest_k_stars(2, &sin2);
    assert(2 == closest_stars.size());
    assert(closest_stars[0].distance() == (Star{1, 2, 3}.distance()));
    assert(closest_stars[1].distance() == (Star{3, 2, 1}.distance()));
}

int main(int argc, char* argv[])
{
    simple_test();
    random_device rd;
    default_random_engine gen(rd());
    for (int times = 0; times < 1000; ++times) {
        int num, k;
        if (argc == 2) {
            num = stoi(argv[1]);
            uniform_int_distribution<int> dis(1, num);
            k = dis(gen);
        } else if (argc == 3) {
            num = stoi(argv[1]);
            k = stoi(argv[2]);
        } else {
            uniform_int_distribution<int> num_dis(1, 10000);
            num = num_dis(gen);
            uniform_int_distribution<int> k_dis(1, num);
            k = k_dis(gen);
        }
        vector<Star> stars;
        // Randomly generate num of stars.
        uniform_real_distribution<double> dis(0, 10000);
        for (int i = 0; i < num; ++i) {
            stars.emplace_back(Star{dis(gen), dis(gen), dis(gen)});
        }
        istringstream sin(CreateStreamingString(stars));
        vector<Star> closest_stars(find_closest_k_stars(k, &sin));
        sort(closest_stars.begin(), closest_stars.end());
        sort(stars.begin(), stars.end());
        cout << "k = " << k << "\n";
        cout << stars[k - 1].x << " " << stars[k - 1].y << " " << stars[k - 1].z
             << " " << stars[k - 1].distance() << "\n";
        cout << closest_stars.back().x << " " << closest_stars.back().y << " "
             << closest_stars.back().z << " " << closest_stars.back().distance() << "\n";
        assert(fabs(stars[k - 1].distance() - closest_stars.back().distance()) < 1.0e-2);
    }
    return 0;
}
