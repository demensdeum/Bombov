cmake_minimum_required(VERSION 3.29)

set(PROJECT_NAME Bombov)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

include_directories(.)

file(GLOB_RECURSE SOURCE_FILES
    "*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})