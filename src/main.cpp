#include "ShaderProgram.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Window.h"

#include <SDL3/SDL.h>
#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main() {
    Window window("GameEngine", 800, 600);
    
    if(!window.isValid()){
        return 0; // exit early
    }

    glEnable(GL_DEPTH_TEST);

    bool running = true;
    SDL_Event event;

    // 1. Define the triangle's coordinates.
    const float vertices[] = {
        -0.0f, -0.5f, 0.0f,
        1.0f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f
    };

    const float rectangleVertices[] = {
    // Triangle 1
        -1.0f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,

        // Triangle 2
        -1.0f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,
        -1.0f,  0.5f, 0.0f
    };

    
    
    const char* vertexShaderSource = R"glsl(
        #version 150 core

        in vec3 aPosition;
        uniform mat4 uModel;
        uniform mat4 uProjection;

        void main() {
            gl_Position = uProjection * uModel * vec4(aPosition, 1.0);
        }
    )glsl";

    const char* fragmentShaderSource = R"glsl(
        #version 150 core

        out vec4 outColor;

        void main() {
            outColor = vec4(1.0, 0.2, 0.2, 1.0);
        }
    )glsl";

    int exitCode = 0;

    {
        ShaderProgram program(vertexShaderSource, fragmentShaderSource); // Create a program object
        Mesh triangle(vertices, 3);
        Mesh rectangle(rectangleVertices, 6);
        Renderer renderer;
        Transform triangleTransform;

        if (!program.isValid() || !triangle.isValid()) {
            SDL_Log("Shader or mesh program setup failure!");
            exitCode = 1;
        }
        else{
            while (running) {
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_EVENT_QUIT ||
                        (event.type == SDL_EVENT_KEY_DOWN &&
                        event.key.key == SDLK_ESCAPE)) {
                        running = false;
                    }
                }
                int width = 0;
                int height = 0;

                if (window.getWindowSize(width, height) && width > 0 && height > 0) {

                    glViewport(0, 0, width, height);

                    float aspect = static_cast<float>(width)
                                / static_cast<float>(height);

                    glm::mat4 projection = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 100.0f);
            
                    glClearColor(0.08f, 0.10f, 0.16f, 1.0f);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    triangleTransform.translate(0.0f, 0.0f, -3.0f);
                    triangleTransform.setRotation(0.0f, 0.0f, glm::radians(90.0f));

                    renderer.render(program, triangle, triangleTransform, projection);
                    renderer.render(program, rectangle, triangleTransform, projection);

                    window.swapBuffers();
                }
            }
        }
    }

    return exitCode;
}