cmake_minimum_required(VERSION 3.29)

set(PROJECT_NAME Bombov)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

include_directories(.)

file(GLOB_RECURSE SOURCE_FILES
    "*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} SDL2 GL GLEW)