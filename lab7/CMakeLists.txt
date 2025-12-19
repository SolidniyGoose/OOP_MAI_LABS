cmake_minimum_required(VERSION 3.10)
project(Lab7_Async_Programming)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа
add_executable(lab7
    src/main.cpp
    src/npc.cpp
    src/dragon.cpp
    src/bull.cpp
    src/frog.cpp
    src/observer.cpp
    src/factory.cpp
    src/world.cpp
    src/visitor.cpp
    src/battle_visitor.cpp
    src/game.cpp
)

target_include_directories(lab7 PRIVATE include)

# Подключаем библиотеку потоков
find_package(Threads REQUIRED)
target_link_libraries(lab7 Threads::Threads)

# Устанавливаем выходную директорию
set_target_properties(lab7 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    OUTPUT_NAME "lab7"
)

# Тесты с Google Test
# В MSYS2 пути могут быть специфичными, попробуем несколько способов

# Способ 1: Ищем пакет
find_package(GTest QUIET)

# Способ 2: Если не нашли, пробуем альтернативные пути
if(NOT GTest_FOUND)
    message(STATUS "GTest не найден стандартным способом, пробуем альтернативные пути...")
    
    # Пробуем найти в типичных местах MSYS2
    set(GTEST_POSSIBLE_PATHS
        /ucrt64
        /mingw64
        C:/msys64/ucrt64
        C:/msys64/mingw64
        $ENV{MSYS2_ROOT}/ucrt64
    )
    
    foreach(path ${GTEST_POSSIBLE_PATHS})
        if(EXISTS ${path}/include/gtest/gtest.h)
            message(STATUS "Найден GTest в: ${path}")
            set(GTEST_INCLUDE_DIR ${path}/include)
            set(GTEST_LIBRARY ${path}/lib/libgtest.a)
            set(GTEST_MAIN_LIBRARY ${path}/lib/libgtest_main.a)
            set(GTEST_FOUND TRUE)
            break()
        endif()
    endforeach()
endif()

if(GTEST_FOUND)
    message(STATUS "Сборка тестов включена")
    
    add_executable(lab7_tests
        tests/test.cpp
        src/npc.cpp
        src/dragon.cpp
        src/bull.cpp
        src/frog.cpp
        src/observer.cpp
        src/factory.cpp
        src/world.cpp
        src/visitor.cpp
        src/battle_visitor.cpp
        src/game.cpp
    )
    
    target_include_directories(lab7_tests PRIVATE include)
    
    # Для MSYS2 могут потребоваться дополнительные include директории
    if(GTEST_INCLUDE_DIR)
        target_include_directories(lab7_tests PRIVATE ${GTEST_INCLUDE_DIR})
    endif()
    
    if(GTEST_LIBRARY AND GTEST_MAIN_LIBRARY)
        # Если нашли библиотеки напрямую
        target_link_libraries(lab7_tests 
            ${GTEST_LIBRARY} 
            ${GTEST_MAIN_LIBRARY} 
            Threads::Threads)
    else()
        # Стандартный способ
        target_link_libraries(lab7_tests GTest::gtest_main Threads::Threads)
    endif()
    
    set_target_properties(lab7_tests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        OUTPUT_NAME "lab7_tests"
    )
    
    # Добавляем тест в CTest
    enable_testing()
    add_test(NAME lab7_tests COMMAND lab7_tests)
    
else()
    message(WARNING "Google Test не найден. Тесты не будут собраны.")
    message(STATUS "Для сборки тестов установите Google Test в MSYS2:")
    message(STATUS "  pacman -S mingw-w64-ucrt-x86_64-gtest")
endif()