cmake_minimum_required(VERSION 3.14)
project(Llgl_Test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -Wall -Wextra -Wpedantic -Werror
    -Wno-error=unused-function -Wno-error=unused-variable
    -Wno-unused-parameter -Wno-sign-compare
)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_definitions(-DTEST)

FILE(GLOB TEST_SOURCE_DIR
    ../src/*.cpp
    *.cpp
)

add_executable(${PROJECT_NAME} 
    ${TEST_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} 
PRIVATE
    gtest gtest_main Llgl
)

target_include_directories(${PROJECT_NAME} 
PRIVATE
    ${PROJECT_SOURCE_DIR}/../glad/include
)

add_test(
    NAME ${PROJECT_NAME} 
    COMMAND ${PROJECT_NAME} 
)