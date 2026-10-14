#include "ShaderProgram.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Window.h"

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main() {
    Window window("GameEngine", 800, 600); // Create an SDL Window that is already resizable by default
    
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
        -0.5f, -0.5f, -0.5f,        0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,        0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,        0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,        0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,        0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,        0.0f, 0.0f, 1.0f,


        // Right face (+X)
        0.5f, -0.5f,  0.5f,        0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,        0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,        0.0f, 0.0f, 1.0f,

        0.5f, -0.5f,  0.5f,        0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,        0.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,        0.0f, 0.0f, 1.0f,


        // Left face (-X)
        -0.5f, -0.5f, -0.5f,        0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,        0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,        0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,        0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,        0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,        0.0f, 0.0f, 1.0f,


        // Top face (+Y)
        -0.5f,  0.5f,  0.5f,        0.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,        0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,        0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,        0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,        0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,        0.0f, 0.0f, 1.0f,


        // Bottom face (-Y)
        -0.5f, -0.5f,  0.5f,        0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,        0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,        0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,        0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,        0.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,        0.0f, 0.0f, 1.0f
    };// fully pasted from chatgpt ( i get it i just don't want to type all that out )

    
    
    const char* vertexShaderSource = R"glsl(
        #version 150 core

        in vec3 aPosition;
        in vec3 aNormal;

        uniform mat4 uModel;
        uniform mat4 uProjection;

        out vec3 vFragPos;
        out vec3 vNormal;

        void main() {
            vec4 worldPosition = uModel * vec4(aPosition, 1.0);

            vFragPos = worldPosition.xyz;
            vNormal = mat3(transpose(inverse(uModel))) * aNormal;

            gl_Position = uProjection * worldPosition;
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
            // Direction perpendicular to the surface
            vec3 N = normalize(vNormal);

            // Direction from the surface toward the light
            vec3 L = normalize(lightPos - vFragPos);

            // Calculate diffuse intensity
            float diffuseStrength = max(dot(N, L), 0.0);

            // Combine lighting with the object's color
            vec3 diffuse = diffuseStrength * lightColor * objectColor;

            outColor = vec4(diffuse, 1.0);
        }
    )glsl";

    int exitCode = 0;

    {
        ShaderProgram program(vertexShaderSource, fragmentShaderSource); // Create a program object

        Mesh cube(cubeVertices, 36);
        Mesh triangle(vertices, 3);
        Mesh rectangle(rectangleVertices, 6);
        Renderer renderer;
        Transform triangleTransform;
        Transform cubeTransform;
        cubeTransform.setPosition(0.0f, 0.0f, -3.0f);



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

                    //triangleTransform.translate(0.0f, 0.0f, -3.0f);
                    //triangleTransform.setRotation(0.0f, 0.0f, glm::radians(90.0f));

                    cubeTransform.rotate(glm::radians(1.0f), glm::radians(1.0f), 0.0f);


                    renderer.render(program, cube, cubeTransform, projection);
                    window.swapBuffers();
                }
            }
        }
    }

    return exitCode;
}