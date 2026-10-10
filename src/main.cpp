#include <SDL3/SDL.h>
#include <OpenGL/gl3.h>
GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char log[1024] = {};
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);

        SDL_Log("Shader compilation failed: %s", log);

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

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

    GLuint vertexShader =
    compileShader(GL_VERTEX_SHADER, vertexShaderSource);

    GLuint fragmentShader =
    compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    if (!vertexShader || !fragmentShader) {
        if (vertexShader) glDeleteShader(vertexShader);
        if (fragmentShader) glDeleteShader(fragmentShader);

        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
        SDL_GL_DestroyContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Log("Both shaders compiled successfully.");

    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    // Match the vertex shader input to your VAO's attribute location.
    glBindAttribLocation(program, 0, "aPosition");

    glLinkProgram(program);

    GLint linked = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if (!linked) {
        char log[1024] = {};
        glGetProgramInfoLog(program, sizeof(log), nullptr, log);

        SDL_Log("Program linking failed: %s", log);

        glDeleteProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);

        SDL_GL_DestroyContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Log("Shader program linked successfully.");
    
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
        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}