cmake_minimum_required(VERSION 3.10)
project(lab3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB SRC_FILES 
    src/Point.cpp
    src/Figure.cpp  
    src/Trapezoid.cpp
    src/Rhomb.cpp
    src/Pentagon.cpp
    src/FigureArray.cpp
)

add_library(figure_lib ${SRC_FILES})

target_include_directories(figure_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(main src/main.cpp)
target_link_libraries(main figure_lib)

enable_testing()

add_executable(tests test/tests.cpp)
target_link_libraries(tests figure_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)