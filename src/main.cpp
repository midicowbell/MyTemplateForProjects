#include "algos.h"
#include "../libGraph/graph.h"

int main() {
	int h = 8;
	int w = 12;
	int entrX = 0;
	int entrY = w - 1;

	int r = 2 * h + 1;
	int c = 2 * w + 1;
	std::vector<std::pair<int, int>> empty_data;
	std::vector<std::vector<bool>> maze = generate(entrX, entrY, h, w);
	AdjListGraph<int> graph(r * c, false, false, empty_data);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (!maze[i][j]) {
				int u = i * c + j;

				if (j + 1 < c && !maze[i][j + 1]) {
					int v_right = i * c + (j + 1);
					graph.add_edge(u, v_right);
				}
				if (i + 1 < r && !maze[i + 1][j]) {
					int v_down = (i + 1) * c + j;
					graph.add_edge(u, v_down);
				}
			}
		}
	}
	int start = 0 * c + (2 * entrX + 1);
	int end = (2 * h) * c + (2 * entrY + 1);
	std::vector<int> path = graph.dijkstra(start, end);
	if (path.empty()) {
		std::cout << "путь не найден!";
	}
	else {
		printMinPath(maze, path);
	}

}