#pragma once
#include <glm/glm.hpp>

enum class MovementDirection{
    Forward,
    Backward,
    Left,
    Right
};

class Camera{
    public:
        Camera(glm::vec3 position, glm::vec3 direction);

        glm::vec3 getPosition() const;
        glm::vec3 getDirection() const;

        void setPosition(glm::vec3 position);
        void setDirection(glm::vec3 direction);

        void move(MovementDirection direction, float deltaTime);
        void processMouseMovement(float xOffset, float yOffset);

        void save(); // Save position
        void reset(); // Load position

        glm::mat4 getViewMatrix() const;

    private:
        float yaw = -90.0f; //euler angle for horizontal 
        float pitch = 0.0f; // euler angle for vertical
        glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 cameraPosition;
        glm::vec3 cameraDirection;
        glm::vec3 resetPosition; // this one's just so we can reset the original camera position (in case we get lost - don't know why we would but i know i would)
        //glm::vec3 resetDirection;
};