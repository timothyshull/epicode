// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <deque>
#include <iostream>
#include <random>
#include <vector>

using std::boolalpha;
using std::cout;
using std::default_random_engine;
using std::deque;
using std::endl;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

struct GraphVertex;

bool has_cycle(GraphVertex*);

// @include
struct GraphVertex {
    enum Color { white, gray, black } color = white;
    vector<GraphVertex*> edges;
};

bool is_deadlocked(vector<GraphVertex>* G)
{
    return any_of(begin(*G), end(*G), [](GraphVertex& vertex) {
        return vertex.color == GraphVertex::white && has_cycle(&vertex);
    });
}

bool has_cycle(GraphVertex* cur)
{
    // Visiting a gray vertex means a cycle.
    if (cur->color == GraphVertex::gray) {
        return true;
    }

    cur->color = GraphVertex::gray;  // Marks current vertex as a gray one.
    // Traverse the neighbor vertices.
    for (GraphVertex*& next : cur->edges) {
        if (next->color != GraphVertex::black) {
            if (has_cycle(next)) {
                return true;
            }
        }
    }
    cur->color = GraphVertex::black;  // Marks current vertex as black.
    return false;
}
// @exclude

bool has_cycle_exclusion(GraphVertex* cur)
{
    if (cur->color == GraphVertex::black) {
        return true;
    }
    cur->color = GraphVertex::black;
    for (GraphVertex*& next : cur->edges) {
        if (has_cycle_exclusion(next)) {
            return true;
        }
    }
    return false;
}

// O(n^2) check answer.
bool check_answer(vector<GraphVertex>* G)
{
    // marks all vertices as white.
    for (GraphVertex& n : *G) {
        n.color = GraphVertex::white;
    }

    for (GraphVertex& g : *G) {
        if (has_cycle_exclusion(&g)) {
            return true;
        }
        // Reset color to white.
        for (GraphVertex& n : *G) {
            n.color = GraphVertex::white;
        }
    }
    return false;
}

void test_two_nodes_cycle()
{
    vector<GraphVertex> G(2);
    G[0].edges.emplace_back(&G[1]);
    G[1].edges.emplace_back(&G[0]);
    bool result = is_deadlocked(&G);
    cout << boolalpha << result << "\n";
    assert(check_answer(&G) == result);
    assert(result);
}

void test_directed_cycle()
{
    vector<GraphVertex> G(3);
    G[0].edges.emplace_back(&G[1]);
    G[1].edges.emplace_back(&G[2]);
    G[2].edges.emplace_back(&G[0]);
    bool result = is_deadlocked(&G);
    cout << boolalpha << result << "\n";
    assert(check_answer(&G) == result);
    assert(result);
}

void test_directed_star_tree()
{
    vector<GraphVertex> G(4);
    G[0].edges.emplace_back(&G[1]);
    G[0].edges.emplace_back(&G[2]);
    G[0].edges.emplace_back(&G[3]);
    bool result = is_deadlocked(&G);
    cout << boolalpha << result << "\n";
    assert(check_answer(&G) == result);
    assert(!result);
}

void test_directed_line_tree()
{
    vector<GraphVertex> G(4);
    G[0].edges.emplace_back(&G[1]);
    G[1].edges.emplace_back(&G[2]);
    G[2].edges.emplace_back(&G[3]);
    bool result = is_deadlocked(&G);
    cout << boolalpha << result << "\n";
    assert(check_answer(&G) == result);
    assert(!result);
    G[3].edges.emplace_back(&G[1]);
    result = is_deadlocked(&G);
    assert(result);
}

void test_directed_binary_tree()
{
    vector<GraphVertex> G(7);
    G[0].edges.emplace_back(&G[1]);
    G[0].edges.emplace_back(&G[2]);
    G[1].edges.emplace_back(&G[3]);
    G[1].edges.emplace_back(&G[4]);
    G[2].edges.emplace_back(&G[5]);
    G[2].edges.emplace_back(&G[6]);
    bool result = is_deadlocked(&G);
    cout << boolalpha << result << "\n";
    assert(check_answer(&G) == result);
    assert(!result);
    G[4].edges.emplace_back(&G[6]);
    G[6].edges.emplace_back(&G[1]);
    result = is_deadlocked(&G);
    assert(result);
}

void test_directed_two_separate_cycles()
{
    vector<GraphVertex> G(6);
    G[0].edges.emplace_back(&G[1]);
    G[1].edges.emplace_back(&G[2]);
    G[2].edges.emplace_back(&G[0]);
    G[3].edges.emplace_back(&G[4]);
    G[4].edges.emplace_back(&G[5]);
    G[5].edges.emplace_back(&G[3]);
    bool result = is_deadlocked(&G);
    assert(result);
}

int main(int argc, char* argv[])
{
    test_two_nodes_cycle();
    test_directed_cycle();
    test_directed_star_tree();
    test_directed_line_tree();
    test_directed_binary_tree();
    test_directed_two_separate_cycles();
    random_device rd;
    default_random_engine gen(rd());
    for (int times = 0; times < 100; ++times) {
        int n;
        if (argc == 2) {
            n = atoi(argv[1]);
        } else {
            uniform_int_distribution<int> dis(2, 2000);
            n = dis(gen);
        }
        vector<GraphVertex> G(n);
        uniform_int_distribution<int> dis(1, n * (n - 1) / 2);
        int m = dis(gen);
        vector<deque<bool>> is_edge_exist(n, deque<bool>(n, false));
        // Make the graph become connected.
        for (int i = 1; i < n; ++i) {
            G[i - 1].edges.emplace_back(&G[i]);
            G[i].edges.emplace_back(&G[i - 1]);
            is_edge_exist[i - 1][i] = is_edge_exist[i][i - 1] = true;
        }
        // Generate edges randomly.
        m -= (n - 1);
        while (m-- > 0) {
            int a, b;
            do {
                uniform_int_distribution<int> dis(0, n - 1);
                a = dis(gen), b = dis(gen);
            } while (a == b || is_edge_exist[a][b] == true);
            is_edge_exist[a][b] = is_edge_exist[b][a] = true;
            G[a].edges.emplace_back(&G[b]);
            G[b].edges.emplace_back(&G[a]);
        }

        bool result = is_deadlocked(&G);
        cout << boolalpha << result << "\n";
        assert(check_answer(&G) == result);
    }
    return 0;
}
