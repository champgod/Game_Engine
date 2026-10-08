cmake_minimum_required(VERSION 3.25)

project(GameEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(GameEngine
    src/main.cpp
)