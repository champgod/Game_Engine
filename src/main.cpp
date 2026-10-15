#include "ShaderProgram.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Window.h"
#include "Light.h"

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main() {
    Window window("GameEngine", 800, 600); // Create an SDL Window that is already resizable by default

    if (!window.setRelativeMouseMode(true)) {
        SDL_Log("Failed to enable relative mouse mode: %s",
                SDL_GetError());
    }
    
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

    const float cubeVertices[] = {
        // Front face (+Z)
        // Position                 Normal
        -0.5f, -0.5f,  0.5f,        0.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,        0.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,        0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,        0.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,        0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,        0.0f, 0.0f, 1.0f,


        // Back face (-Z)
        -0.5f, -0.5f, -0.5f,        0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,        0.0f, 0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,        0.0f, 0.0f, -1.0f,

        -0.5f, -0.5f, -0.5f,        0.0f, 0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,        0.0f, 0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,        0.0f, 0.0f, -1.0f,


        // Right face (+X)
        0.5f, -0.5f,  0.5f,        1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,        1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,        1.0f, 0.0f, 0.0f,

        0.5f, -0.5f,  0.5f,        1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,        1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,        1.0f, 0.0f, 0.0f,


        // Left face (-X)
        -0.5f, -0.5f, -0.5f,        -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,        -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,        -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,        -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,        -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,        -1.0f, 0.0f, 0.0f,


        // Top face (+Y)
        -0.5f,  0.5f,  0.5f,        0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,        0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,        0.0f, 1.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,        0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,        0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,        0.0f, 1.0f, 0.0f,


        // Bottom face (-Y)
        -0.5f, -0.5f,  0.5f,        0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,        0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,        0.0f, -1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,        0.0f, -1.0f, 0.0f
    };// fully pasted from chatgpt ( i get it i just don't want to type all that out )

    
    
    const char* vertexShaderSource = R"glsl(
        #version 150 core

        in vec3 aPosition;
        in vec3 aNormal;

        uniform mat4 uView;
        uniform mat4 uModel;
        uniform mat4 uProjection;

        out vec3 vFragPos;
        out vec3 vNormal;

        void main() {
            vec4 worldPosition = uModel * vec4(aPosition, 1.0);

            vFragPos = worldPosition.xyz;
            vNormal = mat3(transpose(inverse(uModel))) * aNormal;

            gl_Position =  uProjection * uView * worldPosition; // P V M v (projection * view * model * vector)
        }
    )glsl";

    const char* fragmentShaderSource = R"glsl(
        #version 150 core

        in vec3 vFragPos;
        in vec3 vNormal;

        out vec4 outColor;

        uniform vec3 lightPos;
        uniform vec3 lightColor;
        uniform vec3 objectColor;

        void main() {
            float ambientStrength = 0.1;
            vec3 ambient = ambientStrength * lightColor;

            vec3 N = normalize(vNormal);
            vec3 L = normalize(lightPos - vFragPos);

            float diffuseStrength = max(dot(N, L), 0.0);
            vec3 diffuse = diffuseStrength * lightColor;

            // Combine ambient and diffuse lighting with the object's color
            vec3 result = (ambient + diffuse) * objectColor;
            outColor = vec4(result, 1.0);
        }
    )glsl";

    int exitCode = 0;

    {
        ShaderProgram program(vertexShaderSource, fragmentShaderSource); // Create a program object
        Light light(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.5f, -1.0f, 1.0f));
        Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

        Mesh cube(cubeVertices, 36);
        Renderer renderer;
        
        Transform cubeTransform;
        cubeTransform.setPosition(0.0f, 0.0f, -3.0f);



        if (!program.isValid() || !cube.isValid()) {
            SDL_Log("Shader or mesh program setup failure!");
            exitCode = 1;
        }
        else{
            Uint64 previousTicks = SDL_GetTicks();
            while (running) {
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_EVENT_QUIT ||
                        (event.type == SDL_EVENT_KEY_DOWN &&
                        event.key.key == SDLK_ESCAPE)) {
                        running = false;
                    }
                    if (event.type == SDL_EVENT_MOUSE_MOTION) {
                        camera.processMouseMovement(event.motion.xrel, event.motion.yrel);
                    }   
                }
                const bool* keys = SDL_GetKeyboardState(nullptr);
                Uint64 currentTicks = SDL_GetTicks();
                float deltaTime = (currentTicks - previousTicks) / 1000.0f;
                previousTicks = currentTicks;
                if (keys[SDL_SCANCODE_W]) {
                    camera.move(MovementDirection::Forward, deltaTime);
                }
                if (keys[SDL_SCANCODE_S]) {
                    camera.move(MovementDirection::Backward, deltaTime);
                }
                if (keys[SDL_SCANCODE_A]) {
                    camera.move(MovementDirection::Left, deltaTime);
                }
                if (keys[SDL_SCANCODE_D]) {
                    camera.move(MovementDirection::Right, deltaTime);
                }
                if (keys[SDL_SCANCODE_R]){
                    camera.reset();
                }
                if (keys[SDL_SCANCODE_L]){
                    SDL_Log("New position saved!");
                    camera.save();
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

                    cubeTransform.rotate(glm::radians(0.0f), glm::radians(1.0f), 0.0f);
    
                    light.setPosition(camera.getPosition());
                    renderer.render(program, cube, cubeTransform, projection, light, camera);
                    window.swapBuffers();
                }
            }
        }
    }

    return exitCode;
}