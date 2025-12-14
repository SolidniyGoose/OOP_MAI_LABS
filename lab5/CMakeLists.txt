cmake_minimum_required(VERSION 3.10)
project(lab4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
    TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(queue_lib INTERFACE)

target_include_directories(queue_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(main
    main.cpp
    src/DynamicMemory.cpp
)

target_link_libraries(main PRIVATE queue_lib)

set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

enable_testing()

add_executable(tests
    test/tests.cpp
    src/DynamicMemory.cpp
)

target_link_libraries(tests
    PRIVATE
    queue_lib
    GTest::gtest_main
)

set_target_properties(tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

include(GoogleTest)
gtest_discover_tests(tests)

install(TARGETS main DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)

add_custom_target(run
    DEPENDS main
    COMMAND ${CMAKE_BINARY_DIR}/main
)

add_custom_target(test_run
    DEPENDS tests
    COMMAND ${CMAKE_BINARY_DIR}/tests
)

add_custom_target(all_targets
    DEPENDS main tests
)
