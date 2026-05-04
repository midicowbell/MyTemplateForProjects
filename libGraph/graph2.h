#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <list>

class AdjMatirxGraph {
private:
	std::vector<std::vector<int>> _matrix;
	bool _isOriented;
	bool _isWeighted;
	int _vertices;
public:
	AdjMatirxGraph(int n, bool oriented, bool weighted)
		: _vertices(n), _isOriented(oriented), _isWeighted(weighted) {
		_matrix.resize(n, std::vector<int>(n, 0));
	}
	void addEdge(int u, int v, int weight) {
		int value;

		if (_isWeighted) {
			value = weight;
		}
		else {
			value = 1;
		}
		_matrix[u][v] = value;
		if (!_isOriented) {
			_matrix[v][u] = value;
		}
	}
	void removeVertex(int v) {
		if (v >= _vertices || v < 0) return;

		for (int i = 0; i < _vertices; i++) {
			_matrix[v][i] = 0;
			_matrix[i][v] = 0; 
		}
	}
	void removeEdge(int u, int v) {
		_matrix[u][v] = 0;
		if (_isOriented == false) {
			_matrix[v][u] = 0;
		}
	}
	void print() {
			std::cout << "    ";
			for (int j = 0; j < _vertices; j++) {
				std::cout << j << " ";
			}
			std::cout << std::endl;

			std::cout << "    ";
			for (int j = 0; j < _vertices; j++) {
				std::cout << "--";
			}
			std::cout << std::endl;
			for (int i = 0; i < _vertices; i++) {
				std::cout << i << " | ";

				for (int j = 0; j < _vertices; j++) {
					std::cout << _matrix[i][j] << " ";
				}
				std::cout << std::endl;
		}
	}
};