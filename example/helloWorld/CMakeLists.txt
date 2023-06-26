cmake_minimum_required(VERSION 3.10)

project(helloWorld)


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
