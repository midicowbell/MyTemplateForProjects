#include <gtest/gtest.h>
#include <queue>
#include "../libAlgos/algos.h"


//Проверка размера матрицы
TEST(MazeTest, CorrectSize) {
    int N = 5, M = 5;
    auto maze = generate(2, 2, N, M);

    EXPECT_EQ(maze.size(), 2 * N + 1);
    EXPECT_EQ(maze[0].size(), 2 * M + 1);
}

//Проверка, что все клетки открыты
TEST(MazeTest, AllCellsOpen) {
    int N = 3, M = 3;
    auto maze = generate(1, 1, N, M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            EXPECT_FALSE(maze[2 * i + 1][2 * j + 1])
                << "Клетка (" << i << ", " << j << ") должна быть открыта";
        }
    }
}

//Проверка входа
TEST(MazeTest, EntranceExists) {
    int N = 5, M = 5;
    int X = 2;
    auto maze = generate(X, 3, N, M);

    EXPECT_FALSE(maze[0][2 * X + 1])
        << "Вход должен быть открыт в позиции X=" << X;
}

//Проверка выхода
TEST(MazeTest, ExitExists) {
    int N = 5, M = 5;
    int Y = 3;
    auto maze = generate(1, Y, N, M);

    EXPECT_FALSE(maze[2 * N][2 * Y + 1])
        << "Выход должен быть открыт в позиции Y=" << Y;
}

//Минимальный размер (1×1)
TEST(MazeTest, MinimalSize) {
    int N = 1, M = 1;
    auto maze = generate(0, 0, N, M);

    EXPECT_EQ(maze.size(), 3);
    EXPECT_EQ(maze[0].size(), 3);
    EXPECT_FALSE(maze[1][1]) << "Единственная клетка должна быть открыта";
}

//Прямоугольный лабиринт
TEST(MazeTest, RectangularMaze) {
    int N = 2, M = 5;
    auto maze = generate(0, 4, N, M);

    EXPECT_EQ(maze.size(), 2 * N + 1);
    EXPECT_EQ(maze[0].size(), 2 * M + 1);
}

//Большой лабиринт создается без ошибок
TEST(MazeTest, LargeMaze) {
    int N = 10, M = 10;
    auto maze = generate(5, 5, N, M);

    EXPECT_EQ(maze.size(), 2 * N + 1);
    EXPECT_EQ(maze[0].size(), 2 * M + 1);

    int wall_count = 0;
    for (int i = 0; i < 2 * N + 1; i++) {
        for (int j = 0; j < 2 * M + 1; j++) {
            if (maze[i][j]) wall_count++;
        }
    }
    EXPECT_GT(wall_count, 0) << "Должны остаться внешние стены";
}

//Проверка внешних стен (кроме входа/выхода)
TEST(MazeTest, OuterWalls) {
    int N = 3, M = 3;
    int X = 1, Y = 1;
    auto maze = generate(X, Y, N, M);

    for (int i = 0; i < 2 * N + 1; i++) {
        EXPECT_TRUE(maze[i][0]) << "Левая стена должна быть закрыта";
    }

    for (int i = 0; i < 2 * N + 1; i++) {
        EXPECT_TRUE(maze[i][2 * M]) << "Правая стена должна быть закрыта";
    }
}

//Лабиринт не пустой (есть проходы)
TEST(MazeTest, HasPassages) {
    int N = 4, M = 4;
    auto maze = generate(0, 3, N, M);

    int passage_count = 0;
    for (int i = 0; i < 2 * N + 1; i++) {
        for (int j = 0; j < 2 * M + 1; j++) {
            if (!maze[i][j]) passage_count++;
        }
    }

    EXPECT_GT(passage_count, N * M)
        << "Должно быть больше проходов, чем просто клетки";
}

//Разные размеры работают
TEST(MazeTest, VariousSizes) {
    std::vector<std::pair<int, int>> sizes = {
        {1, 1}, {2, 2}, {3, 5}, {5, 3}, {10, 10}
    };

    for (auto [N, M] : sizes) {
        auto maze = generate(0, M - 1, N, M);
        EXPECT_EQ(maze.size(), 2 * N + 1)
            << "Неверный размер для N=" << N << ", M=" << M;
        EXPECT_EQ(maze[0].size(), 2 * M + 1)
            << "Неверный размер для N=" << N << ", M=" << M;
    }
}

//Проверка обработки невалидных входов/выходов
TEST(MazeTest, InvalidInputHandling) {
    int N = 5, M = 5;

    auto maze1 = generate(-1, 2, N, M);
    EXPECT_EQ(maze1.size(), 2 * N + 1)
        << "Должен создать лабиринт даже с невалидным входом";

    auto maze2 = generate(2, M + 5, N, M);
    EXPECT_EQ(maze2.size(), 2 * N + 1)
        << "Должен создать лабиринт даже с невалидным выходом";

    auto maze3 = generate(-1, -1, N, M);
    EXPECT_EQ(maze3.size(), 2 * N + 1)
        << "Должен создать лабиринт даже с обоими невалидными входами";
}

// Проверка количества проходов должно быть достаточным
TEST(MazeTest, AdequatePassages) {
    int N = 5, M = 5;
    auto maze = generate(2, 2, N, M);

    int passage_count = 0;
    for (int i = 0; i < 2 * N + 1; i++) {
        for (int j = 0; j < 2 * M + 1; j++) {
            if (!maze[i][j]) passage_count++;
        }
    }

    int minimum_passages = 2 * N * M - 1;
    EXPECT_GE(passage_count, minimum_passages)
        << "Проходов недостаточно для идеального лабиринта";
}