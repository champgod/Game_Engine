#include "ShaderProgram.h"

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

    // 2. Declare the identifiers.
    GLuint vao = 0;
    GLuint vbo = 0;

    // 3. Create and bind the VAO.
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // 4. Create and bind the VBO.
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // 5. Upload the vertex data.
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    // 6. Configure the VAO to read the vertices.
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        nullptr
    );

    glEnableVertexAttribArray(0);

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

        if (!program.isValid()) {
            SDL_Log("Shader program setup failure!");
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
                glBindVertexArray(vao);
                glDrawArrays(GL_TRIANGLES, 0, 3);

                SDL_GL_SwapWindow(window);
            }
        }
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return exitCode;
}