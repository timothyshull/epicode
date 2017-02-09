// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <utility>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::get;
using std::numeric_limits;
using std::ostream;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

struct Point;
struct Pair_of_points;
struct Pair_of_points_with_distance;

Pair_of_points_with_distance find_closest_pair_points_in_subarray(const vector<Point>& points, int s, int e);

Pair_of_points_with_distance solve_by_enumerate_all_pairs(const vector<Point>& points, int s, int e);

Pair_of_points_with_distance find_closest_pair_in_remain(vector<Point>* points, double d);

double distance(const Point& a, const Point& b);

// @include
struct Point {
    int x;
    int y;

    // @exclude
    friend ostream& operator<<(ostream& os, const Point& p)
    {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
    // @include
};

const int kBruteForceThreshold = 50;

struct Pair_of_points {
    Point p1;
    Point p2;
};

struct Pair_of_points_with_distance {
    Point p1;
    Point p2;
    double distance;
};

Pair_of_points find_closest_pair_points(vector<Point> points)
{
    sort(begin(points), end(points), [](const Point& a, const Point& b) { return a.x < b.x; });
    auto closest_two_points_with_distance = find_closest_pair_points_in_subarray(points, 0, points.size());
    return {closest_two_points_with_distance.p1, closest_two_points_with_distance.p2};
}

// Returns the closest two points and their distance as a tuple in
// points[begin : end - 1].
Pair_of_points_with_distance find_closest_pair_points_in_subarray(
        const vector<Point>& points, int begin, int end)
{
    if (end - begin <= kBruteForceThreshold) {  // Switch to brute-force.
        return solve_by_enumerate_all_pairs(points, begin, end);
    }

    int mid = begin + (end - begin) / 2;
    auto result0 = find_closest_pair_points_in_subarray(points, begin, mid);
    auto result1 = find_closest_pair_points_in_subarray(points, mid, end);
    auto best_result_in_subsets = result0.distance < result1.distance ? result0 : result1;
    // Stores the points whose separation along the X-axis is less than min_d.
    vector<Point> remain;
    for (const Point& p : points) {
        if (abs(p.x - points[mid].x) < best_result_in_subsets.distance) {
            remain.emplace_back(p);
        }
    }

    auto mid_ret = find_closest_pair_in_remain(&remain, best_result_in_subsets.distance);
    return mid_ret.distance < best_result_in_subsets.distance ? mid_ret : best_result_in_subsets;
}

// Returns the closest two points and the distance between them.
Pair_of_points_with_distance solve_by_enumerate_all_pairs(const vector<Point>& points,
                                                          int begin, int end)
{
    Pair_of_points_with_distance ret;
    ret.distance = numeric_limits<double>::max();
    for (int i = begin; i < end; ++i) {
        for (int j = i + 1; j < end; ++j) {
            double dis = distance(points[i], points[j]);
            if (dis < ret.distance) {
                ret = {points[i], points[j], dis};
            }
        }
    }
    return ret;
}

// Returns the closest two points and its distance as a tuple.
Pair_of_points_with_distance find_closest_pair_in_remain(vector<Point>* remain,
                                                         double d)
{
    sort(remain->begin(), remain->end(), [](const Point& a, const Point& b) { return a.y < b.y; });

    // At most six points in remain.
    Pair_of_points_with_distance ret;
    ret.distance = numeric_limits<double>::max();
    for (int i = 0; i < remain->size(); ++i) {
        for (int j = i + 1;
             j < remain->size() && (*remain)[j].y - (*remain)[i].y < d; ++j) {
            double dis = distance((*remain)[i], (*remain)[j]);
            if (dis < ret.distance) {
                ret = {(*remain)[i], (*remain)[j], dis};
            }
        }
    }
    return ret;
}

double distance(const Point& a, const Point& b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
// @exclude

int main(int argc, char* argv[])
{
    random_device rd;
    default_random_engine gen(rd());
    for (int times = 0; times < 50; ++times) {
        int n;
        if (argc == 2) {
            n = atoi(argv[1]);
        } else {
            uniform_int_distribution<int> dis(1, 5000);
            n = dis(gen);
        }
        cout << "num of points = " << n << "\n";
        vector<Point> points;
        uniform_int_distribution<int> dis(0, 9999);
        for (int i = 0; i < n; ++i) {
            points.emplace_back(Point{dis(gen), dis(gen)});
        }
        auto p = find_closest_pair_points(points);
        auto q = solve_by_enumerate_all_pairs(points, 0, points.size());
        cout << "p = " << p.p1 << " " << p.p2 << ", dis = " << distance(p.p1, p.p2) << "\n";
        cout << "q = " << q.p1 << " " << q.p2 << ", dis = " << distance(q.p1, q.p2) << "\n";
        assert(distance(p.p1, p.p2) == q.distance);
    }
    return 0;
}
