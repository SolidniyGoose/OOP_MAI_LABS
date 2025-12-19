cmake_minimum_required(VERSION 3.14)
project(RPG_Dungeon_Editor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)


FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)


if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()


FetchContent_MakeAvailable(googletest)


include_directories(include)


add_executable(rpg_editor
    src/main.cpp
    src/npc.cpp
    src/dragon.cpp
    src/bull.cpp
    src/frog.cpp
    src/observer.cpp
    src/factory.cpp
    src/world.cpp
    src/visitor.cpp
)


enable_testing()

add_executable(rpg_tests
    tests/test.cpp
    src/npc.cpp
    src/dragon.cpp
    src/bull.cpp
    src/frog.cpp
    src/observer.cpp
    src/factory.cpp
    src/world.cpp
    src/visitor.cpp
)


target_link_libraries(rpg_tests GTest::gtest_main)


add_test(NAME RPG_Tests COMMAND rpg_tests)