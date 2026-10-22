cmake_minimum_required(VERSION 3.25)

project(GameEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG COMPONENTS SDL3-shared)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(GameEngine
    src/main.cpp
    src/ShaderProgram.cpp
    src/Mesh.cpp
    src/Renderer.cpp
    src/Transform.cpp
    src/Window.cpp
    src/Light.cpp
    src/Camera.cpp
    src/Input.cpp
    src/stb_image.cpp
    src/Texture.cpp
)

target_link_libraries(
    GameEngine PRIVATE 
        SDL3::SDL3
        OpenGL::GL
        glm::glm
)

target_include_directories(GameEngine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/header
)