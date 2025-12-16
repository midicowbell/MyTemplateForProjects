# 🎯 MyTemplateForProjects

Универсальный шаблон проекта на **C++** с использованием **CMake** и **Google Test**. Подходит для учебных и рабочих задач: есть библиотека, исполняемый файл и модульные тесты.

## 📁 Структура проекта
MyTemplateForProjects/
├── CMakeLists.txt           # главный файл сборки
├── cmake/                  # вспомогательные функции
│   └── functions.cmake
├── lib/                    # библиотека
│   ├── CMakeLists.txt
│   └── example.cpp
├── src/                    # исполняемый файл
│   ├── CMakeLists.txt
│   └── main.cpp
├── tests/                  # модульные тесты
│   ├── CMakeLists.txt
│   └── test_example.cpp
└── third_party/gtest/      # Google Test (подмодуль)
