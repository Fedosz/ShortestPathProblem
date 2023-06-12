#pragma once
#include <iostream>
#include <vector>

void printSolution(std::vector<std::vector<int>> &dist) {
    std::cout << "The following matrix shows the shortest "
        "distances"
        " between every pair of vertices \n";
    for (int i = 0; i < dist.size(); i++) {
        for (int j = 0; j < dist.size(); j++) {
            if (dist[i][j] == INT32_MAX) {
                std::cout << "INF ";
            } else {
                std::cout << dist[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

void floydWarshall(std::vector<std::vector<int>> dist) {

    int i, j, k;

    for (k = 0; k < dist.size(); k++) {
        for (i = 0; i < dist.size(); i++) {
            for (j = 0; j < dist.size(); j++) {
                if (dist[i][j] > (dist[i][k] + dist[k][j])
                    && (dist[k][j] != INT32_MAX && dist[i][k] != INT32_MAX)) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    dist[j][i] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // printSolution(dist);
}