cmake_minimum_required(VERSION 3.10)

project(Llgl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -Wall -Wextra -Wpedantic -Werror
    -Wno-error=unused-function -Wno-error=unused-variable
    -Wno-unused-parameter -Wno-sign-compare
)

cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB SOURCES
    "src/*.cpp"
)

add_library(Llgl STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} 
PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    PRIVATE
    ${OPENGL_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    OpenGL::GL
    glfw
)

add_definitions(${OPENGL_DEFINITIONS})
