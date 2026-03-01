#pragma once
#include "../lib_dsu/dsu.h"
#include <vector>
#include "time.h"
#include <iostream>
std::vector<std::vector<bool>> generate(int entranceX, int entranceY, int height, int width) {


    std::vector<std::vector<bool>> maze(2 * height + 1,
        std::vector<bool>(2 * width + 1, true));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) { 
            maze[2 * i + 1][2 * j + 1] = false;
        }
    }

    srand(time(0));
    DSU dsu(height * width);
    int components = height * width;

    while (components > 1) {
 
        int i = rand() % height;
        int j = rand() % width;
        int cell1 = i * width + j;
        int direction = rand() % 2;

        if (direction == 0 && i < height - 1) {  
            int i2 = i + 1;
            int j2 = j;
            int cell2 = i2 * width + j2;

            if (dsu.find(cell1) != dsu.find(cell2)) {
                dsu.unite(cell1, cell2);
                maze[2 * i + 2][2 * j + 1] = false;
                components--;
            }
        }
        else if (direction == 1 && j < width - 1) { 
            int i2 = i;
            int j2 = j + 1;
            int cell2 = i2 * width + j2;

            if (dsu.find(cell1) != dsu.find(cell2)) {
                dsu.unite(cell1, cell2);
                maze[2 * i + 1][2 * j + 2] = false; 
                components--;
            }
        }
    }

    if (entranceX >= 0 && entranceX < width) {
        maze[0][2 * entranceX + 1] = false; 
    }

    if (entranceY >= 0 && entranceY < height) {
        maze[2 * height][2 * entranceY + 1] = false;
    }

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