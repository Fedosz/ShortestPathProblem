#pragma once
#include <iostream>
#include <climits>
#include <vector>
#include <cmath>

struct Edge {
    int from;
    int to;
    int cost;
};

std::vector<bool> checkUsed(const std::vector<int>& d, const std::vector<Edge>& edges) {
    std::vector<bool> used(static_cast<int>(d.size()), false);

    for (int i = 0; i < static_cast<int>(d.size()); ++i) {
        for (const auto& edge : edges) {
            if ((d[edge.from] != INT_MAX && d[edge.to] > d[edge.from] + edge.cost) || used[edge.from]) {
                used[edge.to] = true;
            }
        }
    }

    return used;
}

void BellmanFord(int destination, const std::vector<Edge>& edges, int count_of_vertices) {
    int n = count_of_vertices;
    int m = static_cast<int>(edges.size());

    std::vector<int> d(n, INT_MAX);
    d[0] = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m; ++j) {
            if (d[edges[j].from] != INT_MAX) {
                if (d[edges[j].to] > d[edges[j].from] + edges[j].cost) {
                    d[edges[j].to] = std::max(INT_MIN, d[edges[j].from] + edges[j].cost);
                }
            }
        }
    }

    auto used = checkUsed(d, edges);

    //return d[destination];
}