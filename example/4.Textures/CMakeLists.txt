cmake_minimum_required(VERSION 3.10)

project(textures)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} 
    "main.cpp"
)

add_subdirectory(
    ${CMAKE_SOURCE_DIR}/../../ ${CMAKE_SOURCE_DIR}/build/Llgl
)


target_link_libraries(${PROJECT_NAME}
PRIVATE
    Llgl
)

enable_testing()
