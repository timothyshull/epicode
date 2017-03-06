// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>

std::vector<int> rand_vector(int len)
{
    std::vector<int> ret;
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<int> dis{0, 99};
    while (--len) { ret.emplace_back(dis(gen)); }
    return ret;
}

struct Item;

int optimum_subject_to_item_capacity(const std::vector<Item>&, int, int, std::vector<std::vector<int>>&);

// @include
struct Item {
    int weight;
    int value;
};

int optimum_subject_to_capacity(const std::vector<Item>& items, int capacity)
{
    // V[i][j] holds the optimum value when we choose from items[0 : i] and have
    // a capacity of j.
    std::vector<std::vector<int>> v(
            items.size(),
            std::vector<int>(static_cast<std::vector<int>::size_type>(capacity + 1), -1)
    );
    // narrow_cast
    return optimum_subject_to_item_capacity(items, static_cast<int>(items.size() - 1), capacity, v);
}

// Returns the optimum value when we choose from items[0 : k] and have a
// capacity of available_capacity.
int optimum_subject_to_item_capacity(const std::vector<Item>& items, int k, int available_capacity, std::vector<std::vector<int>>& v)
{
    // No items can be chosen.
    if (k < 0) { return 0; }

    if (v[k][available_capacity] == -1) {
        int without_curr_item{optimum_subject_to_item_capacity(items, k - 1, available_capacity, v)};
        int with_curr_item{available_capacity < items[k].weight ?
                           0 :
                           items[k].value + optimum_subject_to_item_capacity(items, k - 1, available_capacity - items[k].weight, v)};
        v[k][available_capacity] = std::max(without_curr_item, with_curr_item);
    }
    return v[k][available_capacity];
}
// @exclude

void small_test()
{
    // The example in the book.
    std::vector<Item> items{{20, 65},
                            {8,  35},
                            {60, 245},
                            {55, 195},
                            {40, 65},
                            {70, 150},
                            {85, 275},
                            {25, 155},
                            {30, 120},
                            {65, 320},
                            {75, 75},
                            {10, 40},
                            {95, 200},
                            {50, 100},
                            {40, 220},
                            {10, 99}};
    assert(optimum_subject_to_capacity(items, 130) == 695);

    items = {{5, 60},
             {3, 50},
             {4, 70},
             {2, 30}};
    assert(optimum_subject_to_capacity(items, 5) == 80);
}

int main(int argc, char* argv[])
{
    small_test();
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::vector<int> weight;
    std::vector<int> value;
    int n;
    int w;
    if (argc == 1) {
        std::uniform_int_distribution<int> n_dis{1, 100};
        n = n_dis(gen);
        std::uniform_int_distribution<int> w_dis{1, 1000};
        w = w_dis(gen);
        weight = rand_vector(n);
        value = rand_vector(n);
    } else if (argc == 2) {
        n = atoi(argv[1]);
        std::uniform_int_distribution<int> w_dis{1, 1000};
        w = w_dis(gen);
        weight = rand_vector(n);
        value = rand_vector(n);
    } else {
        n = atoi(argv[1]);
        w = atoi(argv[2]);
        for (int i{0}; i < n; ++i) {
            weight.emplace_back(std::stoi(argv[3 + i]));
        }
        for (int i{0}; i < n; ++i) {
            value.emplace_back(std::stoi(argv[3 + i + n]));
        }
    }
    std::cout << "Weight: ";
    for (int i{0}; i < n; ++i) {
        std::cout << weight[i] << ' ';
    }
    std::cout << "\n" << "Value: ";
    for (int i{0}; i < n; ++i) {
        std::cout << value[i] << ' ';
    }
    std::cout << "\n";
    std::vector<Item> items;
    for (int i{0}; i < weight.size(); ++i) {
        items.emplace_back(Item{weight[i], value[i]});
    }
    std::cout << "Knapsack size = " << w << "\n";
    std::cout << "all value = " << optimum_subject_to_capacity(items, w) << "\n";
    return 0;
}
