#include "ShaderProgram.h"
#include "Mesh.h"

#include <SDL3/SDL.h>
#include <OpenGL/gl3.h>

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return 1;
    }

    // Here's where the SDL Presets go
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_MAJOR_VERSION, 3
    );
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_MINOR_VERSION, 2
    );
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
    );
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_FLAGS,
        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG
    );
    SDL_GL_SetAttribute(
        SDL_GL_DOUBLEBUFFER, 1
    );
    SDL_GL_SetAttribute(
        SDL_GL_DEPTH_SIZE, 24
    );


    SDL_Window* window = SDL_CreateWindow(
        "GameEngine",
        800,
        600,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        SDL_Log("OpenGL context failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_GL_SetSwapInterval(1);

    bool running = true;
    SDL_Event event;

    // 1. Define the triangle's coordinates.
    const float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };
    
    
    const char* vertexShaderSource = R"glsl(
        #version 150 core

        in vec3 aPosition;

        void main() {
            gl_Position = vec4(aPosition, 1.0);
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

                SDL_GetWindowSizeInPixels(window, &width, &height);
                glViewport(0, 0, width, height);

                glClearColor(0.08f, 0.10f, 0.16f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                // Draw the triangle.
                program.use();
                triangle.bind();
                glDrawArrays(GL_TRIANGLES, 0, triangle.getVertexCount());

                SDL_GL_SwapWindow(window);
            }
        }
    }

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return exitCode;
}