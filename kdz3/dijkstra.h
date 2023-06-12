#pragma once
#include <iostream>
#include <vector>
#include <queue>

int64_t searchDijkstra(int destination, const std::vector<std::vector<std::pair<int, int64_t>>>& g) {
    int n = static_cast<int>(g.size());

    std::vector<int> p(n);

    std::vector<int64_t> d(n, INT64_MAX);
    d[0] = 0;

    std::priority_queue<std::pair<int64_t, int>> q;
    q.emplace(0, 0);

    while (!q.empty()) {
        int v = q.top().second;
        int64_t cur_d = -q.top().first;
        q.pop();

        if (cur_d > d[v]) {
            continue;
        }

        for (auto a : g[v]) {
            if (d[v] + a.second < d[a.first]) {
                d[a.first] = d[v] + a.second;
                p[a.first] = v;
                q.emplace(-d[a.first], a.first);
            }
        }
    }

    return d[destination];
}