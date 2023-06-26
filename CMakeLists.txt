cmake_minimum_required(VERSION 3.10)

project(Llgl)

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
