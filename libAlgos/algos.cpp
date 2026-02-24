#include "dsu.h"
#include <vector>
#include "time.h"
#include <iostream>
#include "algos.h"
std::vector<std::vector<bool>> generate(int x, int y, int M, int N) {
	std::vector<std::vector<bool>> maze(2*N+1, std::vector<bool>(2*M+1, true));
	for (int i = 0; i < N; i++) {
		for (int j = 0; i < M; j++) {
			maze[2 * i + 1][2 * j + 1] = false;
		}
	}
	srand(time(0));
	DSU dsu(M * N);
	int components = M * N;
	while (components > 1) {
		int i = rand() % N;
		int j = rand() % M;
		int cell1 = i * M + j;
		int direction = rand() % 2;
		int i2, j2, cell2;
		if (direction == 0 && j < M - 1) {
			i2 = i + 1;
			j2 = j;
			cell2 = i2 * M + j2;
			if (dsu.find(cell1) != dsu.find(cell2)) {
				dsu.unite(cell1, cell2);
				maze[2 * i + 2][2 * j + 1] = false;
				components--;
			}
		}
		else if (direction == 1 && i < N - 1) {
			i2 = i + 1;
			j2 = j;
			cell2 = i2 * M + j2;
			if (dsu.find(cell1) != dsu.find(cell2)) {
				dsu.unite(cell1, cell2);
				maze[2 * i + 2][2 * j + 1] = false;
				components--;
			}
		}
	}
	maze[0][2 * x + 1] = false;
	maze[2*N][2 * y + 1] = false;
	return maze;
}
void print(const std::vector<std::vector<bool>>& maze, int N, int M) {
	for (int i = 0; i < 2 * N + 1; i++) {
		for (int j = 0; j < 2 * M + 1; j++) {
			if (maze[i][j]) {
				std::cout << "##"; 
			}
			else {
				std::cout << "  "; 
			}
		}
		std::cout << std::endl;
	}
}