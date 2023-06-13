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

    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].from;
        int v = edges[i].to;
        int weight = edges[i].cost;
        // Check for negative cycles
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