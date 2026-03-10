#pragma once
#include "../lib_dsu/dsu.h"
#include <vector>
#include "time.h"
#include <iostream>
std::vector<std::vector<bool>> generate(int entranceX, int entranceY, int height, int width);
void print(const std::vector<std::vector<bool>>& maze, int N, int M);