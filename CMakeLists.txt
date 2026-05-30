cmake_minimum_required(VERSION 3.14)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Папки для поиска хедеров во всем проекте
include_directories(lib)
include_directories(libTvector) # Исправил регистр v
include_directories(libUnsortedTableOnVec)
include_directories(lib_list)
include_directories(libSortedTableOnVec)
include_directories(libBSTree)
include_directories(libAVLtree)
include_directories(libRBtree)

add_subdirectory(libITable)
add_subdirectory(libUnsortedTableOnVec)
add_subdirectory(libSortedTableOnVec)
add_subdirectory(libUnsortedTableOnList)
add_subdirectory(libSortedTableOnBST)
add_subdirectory(libSortedTableOnRBTree)
add_subdirectory(src)


option(BUILD_TESTS "Build unit tests?" ON)

if(BUILD_TESTS)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    # Важно: путь должен совпадать с папкой на диске
    add_subdirectory(third_party/googletest EXCLUDE_FROM_ALL)

    enable_testing()
    add_subdirectory(tests) # Идет в папку tests и ищет там CMakeLists.txt
endif()
find_package(Doxygen REQUIRED)

if (DOXYGEN_FOUND)
    # =========================================================
    # БАЗОВЫЕ НАСТРОЙКИ GRAPHVIZ (DOT) И UML
    # =========================================================
    set(DOXYGEN_HAVE_DOT YES)
    set(DOXYGEN_UML_LOOK YES)
    set(DOXYGEN_RECURSIVE YES)
    
    # Пытаемся автоматически найти Graphviz в системе. 
    # Если не находит, раскомментируйте строчку ниже с вашим путем:
    # set(DOXYGEN_DOT_PATH "C:/Program Files/Graphviz/bin") 

    # Исключаем сторонние библиотеки и тесты, чтобы они не засоряли общую схему связей
    set(DOXYGEN_EXCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/third_party" "${CMAKE_CURRENT_SOURCE_DIR}/tests")

    # =========================================================
    # НАСТРОЙКИ ДЛЯ ОТОБРАЖЕНИЯ ПОЛНЫХ ДАННЫХ ВНУТРИ КЛАССОВ
    # =========================================================
    set(DOXYGEN_EXTRACT_ALL YES)         # Извлекать все сущности (даже без комментариев)
    set(DOXYGEN_EXTRACT_PRIVATE YES)     # Показывать private поля и методы (важно для связей объектов)
    set(DOXYGEN_EXTRACT_STATIC YES)      # Показывать static элементы
    set(DOXYGEN_EXTRACT_LOCAL_CLASSES YES) # Включать локальные/вложенные структуры и классы
    set(DOXYGEN_UML_LIMIT_NUM_FIELDS 35) # Лимит полей в карточке класса (35 — оптимально, чтобы граф не стал огромным)
    set(DOXYGEN_TEMPLATE_RELATIONS YES)  # Отображать связи для шаблонов C++ (template <typename T>)

    # =========================================================
    # НАСТРОЙКИ ДЛЯ ПОСТРОЕНИЯ СКВОЗНОЙ ОБЩЕЙ СХЕМЫ СВЯЗЕЙ
    # =========================================================
    set(DOXYGEN_GRAPHICAL_HIERARCHY YES) # Построить общую графическую иерархию всех классов
    set(DOXYGEN_CLASS_GRAPH YES)         # Рисовать графы наследования для каждого класса
    set(DOXYGEN_COLLABORATION_GRAPH YES) # Включить графы взаимодействия (покажет связи использования, композиции и агрегации)
    set(DOXYGEN_DIRECTORY_GRAPH YES)     # Показывать зависимости между вашими папками (libTree, libGraph и т.д.)

    # СНЯТИЕ ОГРАНИЧЕНИЙ НА РАЗМЕР ГРАФА (КРИТИЧЕСКИ ВАЖНО ДЛЯ ПОЛНОЙ СВЯЗИ)
    set(DOXYGEN_DOT_GRAPH_MAX_NODES 500) # Максимальное число классов на одной схеме (по умолчанию всего 50)
    set(DOXYGEN_MAX_DOT_GRAPH_DEPTH 0)   # Использовать бесконечную глубину связей (0), чтобы показать всю цепочку от корня
    set(DOXYGEN_DOT_MULTI_TARGET_SECTIONS YES) # Помогает группировать сложные разветвленные связи

    # Поддержка стандартной библиотеки C++ (чтобы красиво связывались std::vector, std::shared_ptr и т.д.)
    set(DOXYGEN_BUILTIN_STL_SUPPORT YES)

    # Генерация документации
    doxygen_add_docs(doxygen_documentation
        ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Генерация ПОЛНОЙ И СКВОЗНОЙ схемы всех классов проекта..."
    )
endif()