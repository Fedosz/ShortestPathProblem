#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include "dijkstra.h"
#include "Floyd-Warshall.h"
#include "Bellman-Ford.h"

// АиСД-2, 2023, задание 3
// Жуков Фёдор Сергеевич БПИ218
// Visual studio
// Сделано:
// Программа для подсчета времени
// .csv с результатами
// Графики с результатами
// Вывод
// 
// Для проверки алгоритмов достаточно раскомментировать соответствующие строки кода в функциях поиска пути

std::ofstream output;

std::vector<Edge> edges(std::vector<std::vector<int>> matrix) {
	std::vector<Edge> vec;
	for (size_t i = 0; i < matrix.size(); i++) {
		for (size_t j = i; j < matrix.size(); j++) {
			if (i != j && matrix[i][j] != 0) {
				Edge cur;
				cur.from = i;
				cur.to = j;
				cur.cost = matrix[i][j];
				vec.push_back(cur);
			}
		}
	}
	return vec;
}

std::vector<std::vector<std::pair<int, int64_t>>> dijk(std::vector<std::vector<int>> matrix) {
	std::vector<std::vector<std::pair<int, int64_t>>> vec;
	vec.resize(matrix.size());
	for (size_t i = 0; i < matrix.size(); i++) {
		for (size_t j = 0; j < matrix.size(); j++) {
			if (i != j && matrix[i][j] != 0) {
				vec[i].push_back(std::make_pair(j, matrix[i][j]));
			}
		}
	}
	return vec;
}

void dijkstraRoute(std::vector<std::vector<int>>& graph) {
	long long sum = 0;
	auto g = dijk(graph);
	for (int i = 0; i < 5; i++) {
		auto start = std::chrono::high_resolution_clock::now();

		searchDijkstra(graph.size() - 1, g);

		auto elapsed = std::chrono::high_resolution_clock::now() - start;
		long long nanoseconds =
			std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
		sum += nanoseconds;
	}
	sum /= 5;
	output << "dijkstra;" << graph.size() << ";" << sum << std::endl;
}

void fordRoute(std::vector<std::vector<int>>& graph) {
	long long sum = 0;
	std::vector<Edge> vec = edges(graph);
	for (int i = 0; i < 5; i++) {
		auto start = std::chrono::high_resolution_clock::now();

		BellmanFord(graph.size() - 1, vec, graph.size());

		auto elapsed = std::chrono::high_resolution_clock::now() - start;
		long long nanoseconds =
			std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
		sum += nanoseconds;
	}
	sum /= 5;
	output << "bellman-ford;" << graph.size() << ";" << sum << std::endl;
}

void floydRoute(std::vector<std::vector<int>>& graph) {
	for (size_t i = 0; i < graph.size(); i++) {
		for (size_t j = 0; j < graph.size(); j++) {
			if (i != j && graph[i][j] == 0) {
				graph[i][j] = INT32_MAX;
			}
		}
	}
	long long sum = 0;
	for (int i = 0; i < 5; i++) {
		auto start = std::chrono::high_resolution_clock::now();

		floydWarshall(graph);

		auto elapsed = std::chrono::high_resolution_clock::now() - start;
		long long nanoseconds =
			std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
		sum += nanoseconds;
	}
	sum /= 5;
	output << "floyd-warshall;" << graph.size() << ";" << sum << std::endl;
}

int main() {
	std::vector<std::vector<int>> fullGraph, connectedGraph, treeGraph;
	fullGraph.resize(1010);
	connectedGraph.resize(1010);
	treeGraph.resize(1010);
	for (int i = 0; i < 1010; i++) {
		fullGraph[i].resize(1010);
		connectedGraph[i].resize(1010);
		treeGraph[i].resize(1010);
	}

	//задаем сид
	srand(std::time(NULL));

	output.open("tests.csv");

	//генерируем полный граф
	for (size_t i = 0; i < 1010; i++) {
		for (size_t j = 0; j < 1010; j++) {
			if (i == j) {
				fullGraph[i][j] = 0;
			} else {
				int cost = rand() % 10 + 1;
				fullGraph[i][j] = cost;
				fullGraph[j][i] = cost;
			}
		}
	}
	
	//генерируем дерево (разреженный граф)
	int j = 0, i = 1;

	while (i < 1010) {
		int cost = rand() % 10 + 1;
		treeGraph[i][j] = cost;
		treeGraph[j][i] = cost;
		i++;
		if (i < 1010) {
			int cost = rand() % 10 + 1;
			treeGraph[i][j] = cost;
			treeGraph[j][i] = cost;
			j++;
			i++;
		}
	}

	//генерируем связный граф
	j = 0;
	i = 1;

	while (i < 1010) {
		int cost = rand() % 10 + 1;
		connectedGraph[i][j] = cost;
		connectedGraph[j][i] = cost;
		i++;
		if (i < 1010) {
			int cost = rand() % 10 + 1;
			connectedGraph[i][j] = cost;
			connectedGraph[j][i] = cost;
			j++;
			i++;
		}
	}

	double l = 1009;
	while (((2 * l) / (1010 * 1009)) < 0.45) {
		i = rand() % 1010;
		j = rand() % 1010;
		int cost = rand() % 10 + 1;
		while (connectedGraph[i][j] != 0 || i == j) {
			i = rand() % 1010;
			j = rand() % 1010;
		}
		connectedGraph[i][j] = cost;
		connectedGraph[j][i] = cost;
		++l;
	}

	for (int algo = 0; algo < 3; algo++) {
		std::vector<std::vector<int>> cur;
		switch (algo) {
			case 0:
				cur = fullGraph;
				output << "Full graph" << std::endl;
				output << std::endl;
				std::cout << "full started\n";
				break;
			case 1:
				cur = connectedGraph;
				output << "Connected graph" << std::endl;
				output << std::endl;
				std::cout << "connected started\n";
				break;
			case 2:
				cur = treeGraph;
				output << "Tree graph" << std::endl;
				output << std::endl;
				std::cout << "tree started\n";
				break;
		}

		for (int k = 10; k <= 1010; k += 50) {
			std::vector<std::vector<int>> graph;
			graph.resize(k);
			for (int ii = 0; ii < k; ii++) {
				graph[ii].resize(k);
			}
			for (int p = 0;  p < k;  p++) {
				for (int a = 0; a < k; a++) {
					graph[p][a] = cur[p][a];
				}
			}
			std::cout << "dijkstra " << k << "\n";

			dijkstraRoute(graph);
		}

		for (int k = 10; k <= 1010; k += 50) {
			std::vector<std::vector<int>> graph;
			graph.resize(k);
			for (int ii = 0; ii < k; ii++) {
				graph[ii].resize(k);
			}
			for (int p = 0; p < k; p++) {
				for (int a = 0; a < k; a++) {
					graph[p][a] = cur[p][a];
				}
			}

			std::cout << "ford " << k << "\n";

			fordRoute(graph);
		}

		for (int k = 10; k <= 1010; k += 50) {
			std::vector<std::vector<int>> graph;
			graph.resize(k);
			for (int ii = 0; ii < k; ii++) {
				graph[ii].resize(k);
			}
			for (int p = 0; p < k; p++) {
				for (int a = 0; a < k; a++) {
					graph[p][a] = cur[p][a];
				}
			}

			std::cout << "floyd " << k << "\n";

			floydRoute(graph);
		}
	}
	
	output.close();

	std::cout << "Finished";
}