// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <random>

struct Graph_vertex;

bool has_bridge(Graph_vertex*, Graph_vertex*, int);

// @include
struct Graph_vertex {
    int d;
    int l;  // Discovery and leaving time.
    std::vector<Graph_vertex*> edges;

    // @exclude
    Graph_vertex() : d{0}, l{std::numeric_limits<int>::max()} {}
    // @include
};

bool is_graph_fault_tolerant(std::vector<Graph_vertex>& graph)
{
    if (!graph.empty()) { return has_bridge(&graph.front(), nullptr, 0); }
    return true;
}

bool has_bridge(Graph_vertex* cur, Graph_vertex* pre, int time)
{
    cur->d = ++time, cur->l = std::numeric_limits<int>::max();
    for (Graph_vertex*& next : cur->edges) {
        if (next != pre) {
            if (next->d != 0) {  // Back edge.
                cur->l = std::min(cur->l, next->d);
            } else {  // Forward edge.
                if (!has_bridge(next, cur, time)) { return false; }
                cur->l = std::min(cur->l, next->l);
            }
        }
    }
    return (pre == nullptr || cur->l < cur->d);
}
// @exclude

void dfs_exclusion(Graph_vertex* cur, Graph_vertex* a, Graph_vertex* b)
{
    cur->d = 1;
    for (Graph_vertex*& next : cur->edges) {
        if (next->d == 0 &&
            ((cur != a && cur != b) || (next != a && next != b))) {
            dfs_exclusion(next, a, b);
        }
    }
}

// O(n^2) check answer.
bool check_answer(std::vector<Graph_vertex>& graph)
{
    // marks all vertices as white.
    for (Graph_vertex& n : graph) { n.d = 0; }

    for (Graph_vertex& g : graph) {
        for (auto& t : g.edges) {
            dfs_exclusion(&g, &g, t);
            int count{0};
            for (Graph_vertex& n : graph) {
                if (n.d == 1) {
                    ++count;
                    n.d = 0;
                }
            }
            if (count != graph.size()) { return false; }
        }
    }
    return true;
}

void test_triangle()
{
    std::vector<Graph_vertex> graph(3);
    graph[0].edges.emplace_back(&graph[1]);
    graph[1].edges.emplace_back(&graph[0]);
    graph[1].edges.emplace_back(&graph[2]);
    graph[2].edges.emplace_back(&graph[1]);
    graph[2].edges.emplace_back(&graph[0]);
    graph[0].edges.emplace_back(&graph[2]);
    bool result{is_graph_fault_tolerant(graph)};
    assert(result);
}

void test_two_triangles()
{
    std::vector<Graph_vertex> graph(6);
    graph[0].edges.emplace_back(&graph[1]);
    graph[1].edges.emplace_back(&graph[0]);
    graph[1].edges.emplace_back(&graph[2]);
    graph[2].edges.emplace_back(&graph[1]);
    graph[2].edges.emplace_back(&graph[0]);
    graph[0].edges.emplace_back(&graph[2]);

    graph[3].edges.emplace_back(&graph[4]);
    graph[4].edges.emplace_back(&graph[3]);
    graph[4].edges.emplace_back(&graph[5]);
    graph[5].edges.emplace_back(&graph[4]);
    graph[5].edges.emplace_back(&graph[3]);
    graph[3].edges.emplace_back(&graph[5]);

    // bridge edge
    graph[0].edges.emplace_back(&graph[3]);
    graph[3].edges.emplace_back(&graph[0]);

    bool result{is_graph_fault_tolerant(graph)};
    assert(!result);
}

void test_two_triangles_bridged()
{
    std::vector<Graph_vertex> graph(6);
    graph[0].edges.emplace_back(&graph[1]);
    graph[1].edges.emplace_back(&graph[0]);
    graph[1].edges.emplace_back(&graph[2]);
    graph[2].edges.emplace_back(&graph[1]);
    graph[2].edges.emplace_back(&graph[0]);
    graph[0].edges.emplace_back(&graph[2]);

    graph[3].edges.emplace_back(&graph[4]);
    graph[4].edges.emplace_back(&graph[3]);
    graph[4].edges.emplace_back(&graph[5]);
    graph[5].edges.emplace_back(&graph[4]);
    graph[5].edges.emplace_back(&graph[3]);
    graph[3].edges.emplace_back(&graph[5]);

    graph[0].edges.emplace_back(&graph[3]);
    graph[3].edges.emplace_back(&graph[0]);

    graph[0].edges.emplace_back(&graph[4]);
    graph[4].edges.emplace_back(&graph[0]);

    bool result{is_graph_fault_tolerant(graph)};
    assert(result);
}

int main(int argc, char* argv[])
{
    test_triangle();
    test_two_triangles();
    test_two_triangles_bridged();
    std::random_device rd;
    std::default_random_engine gen{rd()};
    for (int times{0}; times < 1000; ++times) {
        std::vector<Graph_vertex> graph;
        int n;
        if (argc == 2) {
            n = std::stoi(argv[1]);
        } else {
            std::uniform_int_distribution<int> dis{2, 101};
            n = dis(gen);
        }
        for (int i{0}; i < n; ++i) { graph.emplace_back(Graph_vertex()); }
        std::uniform_int_distribution<int> dis{1, n * (n - 1) / 2};
        int m{dis(gen)};
        std::vector<std::deque<bool>> is_edge_exist(
                static_cast<std::vector<std::deque<bool>>::size_type>(n),
                std::deque<bool>(static_cast<std::deque<bool>::size_type>(n), false)
        );
        // Make the graph become connected.
        for (int i = 1; i < n; ++i) {
            graph[i - 1].edges.emplace_back(&graph[i]);
            graph[i].edges.emplace_back(&graph[i - 1]);
            is_edge_exist[i - 1][i] = is_edge_exist[i][i - 1] = true;
        }

        // Generate edges randomly.
        m -= (n - 1);
        while (m-- > 0) {
            int a;
            int b;
            dis = std::uniform_int_distribution<int>{0, n - 1};
            do {
                a = dis(gen);
                b = dis(gen);
            } while (a == b || is_edge_exist[a][b] == true);
            is_edge_exist[a][b] = is_edge_exist[b][a] = true;
            graph[a].edges.emplace_back(&graph[b]);
            graph[b].edges.emplace_back(&graph[a]);
        }

        /*
        for (int i = 0; i < G.size(); ++i) {
          cout << i << "\n";
          for (int j = 0; j < G[i].edges.size(); ++j) {
            cout << ' ' << G[i].edges[j];
          }
          cout << "\n";
        }
        */

        bool res{is_graph_fault_tolerant(graph)};
        std::cout << std::boolalpha << res << "\n";
        assert(check_answer(graph) == res);
    }
    return 0;
}
