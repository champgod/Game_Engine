#include "ShaderProgram.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Window.h"
#include "Light.h"
#include "Input.h"
#include "Texture.h"
#include "Material.h"

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <filesystem>

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

    
    const float cubeVertices[] = {
        // Front face (+Z)
        // Position                  Normal                UV
        -0.5f, -0.5f,  0.5f,         0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,         0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,         0.0f,  0.0f,  1.0f,   1.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,         0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,         0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,         0.0f,  0.0f,  1.0f,   0.0f, 1.0f,

        // Back face (-Z)
        -0.5f, -0.5f, -0.5f,         0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,         0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,         0.0f,  0.0f, -1.0f,   0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,         0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,         0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,         0.0f,  0.0f, -1.0f,   0.0f, 0.0f,

        // Right face (+X)
        0.5f, -0.5f,  0.5f,         1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,         1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,         1.0f,  0.0f,  0.0f,   1.0f, 1.0f,

        0.5f, -0.5f,  0.5f,         1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,         1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,         1.0f,  0.0f,  0.0f,   0.0f, 1.0f,

        // Left face (-X)
        -0.5f, -0.5f, -0.5f,        -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,        -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,        -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,        -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,        -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,        -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,

        // Top face (+Y)
        -0.5f,  0.5f,  0.5f,         0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,         0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,         0.0f,  1.0f,  0.0f,   1.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,         0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,         0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,         0.0f,  1.0f,  0.0f,   0.0f, 1.0f,

        // Bottom face (-Y)
        -0.5f, -0.5f,  0.5f,         0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,         0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,         0.0f, -1.0f,  0.0f,   1.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,         0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,         0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,         0.0f, -1.0f,  0.0f,   1.0f, 1.0f
    };// fully pasted from chatgpt ( i get it i just don't want to type all that out )

    
    
    const char* vertexShaderSource = R"glsl(
        #version 150 core

        in vec3 aPosition;
        in vec3 aNormal;
        in vec2 aTexCoord;

        uniform mat4 uView;
        uniform mat4 uModel;
        uniform mat4 uProjection;

        out vec3 vFragPos;
        out vec3 vNormal;
        out vec2 vTexCoord;

        void main() {
            vTexCoord = aTexCoord;
            vec4 worldPosition = uModel * vec4(aPosition, 1.0);

            vFragPos = worldPosition.xyz;
            vNormal = mat3(transpose(inverse(uModel))) * aNormal;

            gl_Position =  uProjection * uView * worldPosition; // P V M v (projection * view * model * vector)
        }
    )glsl";

    const char* fragmentShaderSource = R"glsl(
        #version 150 core

        in vec2 vTexCoord;
        in vec3 vFragPos;
        in vec3 vNormal;

        out vec4 outColor;

        uniform vec3 lightPos;
        uniform vec3 lightColor;

        uniform sampler2D uTexture;
        uniform vec3 objectColor;
        uniform float specularStrength;
        uniform float shininess;

        uniform vec3 cameraPos;

        void main() {
            vec4 texColor = texture(uTexture, vTexCoord);
            
            float ambientStrength = 0.1;
            vec3 ambient = ambientStrength * lightColor;

            vec3 N = normalize(vNormal);
            vec3 L = normalize(lightPos - vFragPos);
            vec3 V = normalize(cameraPos - vFragPos);
            vec3 R = reflect(-L, N);

            float diffuseStrength = max(dot(N, L), 0.0);
            vec3 diffuse = diffuseStrength * lightColor;

            float spec = pow(max(dot(V, R), 0.0), shininess);
            vec3 specular = specularStrength * spec * lightColor;

            // Combine ambient and diffuse lighting with the object's color
            vec3 result = (ambient + diffuse) * texColor.rgb * objectColor + specular;
            outColor = vec4(result, 1.0);
        }
    )glsl";

    int exitCode = 0;

    {
        ShaderProgram program(vertexShaderSource, fragmentShaderSource); // Create a program object
        Light light(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f)); // Create light object
        Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)); // Create camera object

        Mesh cube(cubeVertices, 36); // Create a cube mesh
        Renderer renderer; // Create renderer object
        
        Transform cubeTransform; // Create cube transform object
        cubeTransform.setPosition(0.0f, 0.0f, -3.0f); // Set cube position to (0, 0, -3)
        Input input; // Create an input object
        Texture brickTexture;

        Material cubeMaterial;

        cubeMaterial.setTexture(&brickTexture);
        cubeMaterial.setColor(glm::vec3(1.0f));
        cubeMaterial.setSpecularStrength(0.8f);
        cubeMaterial.setShininess(32.0f);

        SDL_Log("Working directory: %s",
        std::filesystem::current_path().string().c_str());

        SDL_Log("Texture exists: %s",
                std::filesystem::exists("assets/textures/wall.jpg")
                    ? "yes" : "no");

        if (!brickTexture.loadImage("assets/textures/wall.jpg")) {
            SDL_Log("Failed to load brick texture!");
        }


        if (!program.isValid() || !cube.isValid()) {
            SDL_Log("Shader or mesh program setup failure!");
            exitCode = 1;
        }
        else{
            Uint64 previousTicks = SDL_GetTicks();
            while (running) {
                Uint64 currentTicks = SDL_GetTicks();
                float deltaTime = (currentTicks - previousTicks) / 1000.0f;
                previousTicks = currentTicks;

                running = input.processEvent(camera);
                input.updateKeyInput(camera, deltaTime);


                int width = 0;
                int height = 0;

                if (window.getWindowSize(width, height) && width > 0 && height > 0) {

                    glViewport(0, 0, width, height);

                    float aspect = static_cast<float>(width)
                                / static_cast<float>(height);

                    glm::mat4 projection = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 100.0f);
            
                    glClearColor(0.08f, 0.10f, 0.16f, 1.0f);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    //cubeTransform.rotate(glm::radians(0.0f), glm::radians(1.0f), 0.0f);
    
                    //light.setPosition(camera.getPosition());
                    renderer.render(program, cube, cubeTransform, projection, light, camera, brickTexture, cubeMaterial);
                    window.swapBuffers();
                }
            }
        }
    }

    return exitCode;
}