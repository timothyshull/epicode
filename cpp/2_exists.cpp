// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <deque>
#include <iostream>
#include <random>

struct Graph_vertex;

bool has_cycle(Graph_vertex&);

enum class Vertex_color { white, gray, black };

// @include
struct Graph_vertex {
    Vertex_color color = Vertex_color::white;
    std::vector<Graph_vertex*> edges;
};

bool is_deadlocked(std::vector<Graph_vertex>& vertices)
{
    return std::any_of(vertices.begin(), vertices.end(), [](Graph_vertex& vertex) {
        return vertex.color == Vertex_color::white && has_cycle(vertex);
    });
}

bool has_cycle(Graph_vertex& cur)
{
    // Visiting a gray vertex means a cycle.
    if (cur.color == Vertex_color::gray) {
        return true;
    }

    cur.color = Vertex_color::gray;  // Marks current vertex as a gray one.
    // Traverse the neighbor vertices.
    for (auto& next : cur.edges) {
        if (next->color != Vertex_color::black) {
            if (has_cycle(*next)) {
                return true;
            }
        }
    }
    cur.color = Vertex_color::black;  // Marks current vertex as black.
    return false;
}
// @exclude

bool has_cycle_exclusion(Graph_vertex& cur)
{
    if (cur.color == Vertex_color::black) {
        return true;
    }
    cur.color = Vertex_color::black;
    for (auto& next : cur.edges) {
        if (has_cycle_exclusion(*next)) {
            return true;
        }
    }
    return false;
}

// O(n^2) check answer.
bool check_answer(std::vector<Graph_vertex>& graph)
{
    // marks all vertices as white.
    for (Graph_vertex& n : graph) {
        n.color = Vertex_color::white;
    }

    for (Graph_vertex& g : graph) {
        if (has_cycle_exclusion(g)) {
            return true;
        }
        // Reset color to white.
        for (Graph_vertex& n : graph) {
            n.color = Vertex_color::white;
        }
    }
    return false;
}

void test_two_nodes_cycle()
{
    std::vector<Graph_vertex> graph(2);
    graph[0].edges.emplace_back(&graph[1]);
    graph[1].edges.emplace_back(&graph[0]);
    bool result{is_deadlocked(graph)};
    std::cout << std::boolalpha << result << "\n";
    assert(check_answer(graph) == result);
    assert(result);
}

void test_directed_cycle()
{
    std::vector<Graph_vertex> graph(3);
    graph[0].edges.emplace_back(&graph[1]);
    graph[1].edges.emplace_back(&graph[2]);
    graph[2].edges.emplace_back(&graph[0]);
    bool result{is_deadlocked(graph)};
    std::cout << std::boolalpha << result << "\n";
    assert(check_answer(graph) == result);
    assert(result);
}

void test_directed_star_tree()
{
    std::vector<Graph_vertex> graph(4);
    graph[0].edges.emplace_back(&graph[1]);
    graph[0].edges.emplace_back(&graph[2]);
    graph[0].edges.emplace_back(&graph[3]);
    bool result{is_deadlocked(graph)};
    std::cout << std::boolalpha << result << "\n";
    assert(check_answer(graph) == result);
    assert(!result);
}

void test_directed_line_tree()
{
    std::vector<Graph_vertex> graph(4);
    graph[0].edges.emplace_back(&graph[1]);
    graph[1].edges.emplace_back(&graph[2]);
    graph[2].edges.emplace_back(&graph[3]);
    bool result{is_deadlocked(graph)};
    std::cout << std::boolalpha << result << "\n";
    assert(check_answer(graph) == result);
    assert(!result);
    graph[3].edges.emplace_back(&graph[1]);
    result = is_deadlocked(graph);
    assert(result);
}

void test_directed_binary_tree()
{
    std::vector<Graph_vertex> graph(7);
    graph[0].edges.emplace_back(&graph[1]);
    graph[0].edges.emplace_back(&graph[2]);
    graph[1].edges.emplace_back(&graph[3]);
    graph[1].edges.emplace_back(&graph[4]);
    graph[2].edges.emplace_back(&graph[5]);
    graph[2].edges.emplace_back(&graph[6]);
    bool result{is_deadlocked(graph)};
    std::cout << std::boolalpha << result << "\n";
    assert(check_answer(graph) == result);
    assert(!result);
    graph[4].edges.emplace_back(&graph[6]);
    graph[6].edges.emplace_back(&graph[1]);
    result = is_deadlocked(graph);
    assert(result);
}

void test_directed_two_separate_cycles()
{
    std::vector<Graph_vertex> graph(6);
    graph[0].edges.emplace_back(&graph[1]);
    graph[1].edges.emplace_back(&graph[2]);
    graph[2].edges.emplace_back(&graph[0]);
    graph[3].edges.emplace_back(&graph[4]);
    graph[4].edges.emplace_back(&graph[5]);
    graph[5].edges.emplace_back(&graph[3]);
    bool result{is_deadlocked(graph)};
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

    std::random_device rd;
    std::default_random_engine gen{rd()};

    int n{};
    if (argc == 2) {
        n = std::stoi(argv[1]);
    }
    std::uniform_int_distribution<int> dis;
    for (int times{0}; times < 100; ++times) {
        if (argc != 2) {
            dis = std::uniform_int_distribution<int>{2, 2000};
            n = dis(gen);
        }
        std::vector<Graph_vertex> graph{static_cast<std::vector<Graph_vertex>::size_type>(n)};
        dis = std::uniform_int_distribution<int>{1, n * (n - 1) / 2};
        int m{dis(gen)};
        std::vector<std::deque<bool>> does_edge_exist(static_cast<std::vector<std::deque<bool>>::size_type>(n),
                                                      std::deque<bool>(static_cast<std::deque<bool>::size_type>(n), false));

        // Make the graph become connected.
        for (int i{1}; i < n; ++i) {
            graph[i - 1].edges.emplace_back(&graph[i]);
            graph[i].edges.emplace_back(&graph[i - 1]);
            does_edge_exist[i - 1][i] = does_edge_exist[i][i - 1] = true;
        }

        // Generate edges randomly.
        m -= (n - 1);
        while (m-- > 0) {
            int a, b;
            do {
                dis = std::uniform_int_distribution<int>{0, n - 1};
                a = dis(gen);
                b = dis(gen);
            } while (a == b || does_edge_exist[a][b] == true);
            does_edge_exist[a][b] = does_edge_exist[b][a] = true;
            graph[a].edges.emplace_back(&graph[b]);
            graph[b].edges.emplace_back(&graph[a]);
        }

        bool result{is_deadlocked(graph)};
        std::cout << std::boolalpha << result << "\n";
        assert(check_answer(graph) == result);
    }
    return 0;
}
