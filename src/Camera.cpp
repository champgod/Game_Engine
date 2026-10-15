#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Camera::Camera(glm::vec3 position, glm::vec3 direction){
    cameraPosition = position; //sets camera position
    cameraDirection = direction; //sets camera direction
    resetPosition = position; //sets the reset position as where the camera is initially created
    //resetDirection = direction;
}

glm::vec3 Camera::getPosition() const{
    return cameraPosition;
}
glm::vec3 Camera::getDirection() const{
    return cameraDirection;
}

void Camera::setPosition(glm::vec3 position){
    cameraPosition = position;
}
void Camera::setDirection(glm::vec3 direction){
    cameraDirection = direction;
}

void Camera::move(MovementDirection direction, float deltaTime){
    float cameraSpeed = 2.5f;
    glm::vec3 frontBack = glm::normalize(cameraDirection); //faces forward (but we can subtract to move back)
    glm::vec3 rightLeft = glm::normalize(glm::cross(cameraDirection, worldUp)); //faces right (but we can subtract)
    switch (direction) {
        case MovementDirection::Forward:
            cameraPosition += (frontBack * deltaTime * cameraSpeed);
            break;
        case MovementDirection::Backward:
            cameraPosition -= (frontBack * deltaTime * cameraSpeed);
            break;

        case MovementDirection::Left:
            cameraPosition -= (rightLeft * deltaTime * cameraSpeed);
            break;

        case MovementDirection::Right:
            cameraPosition += (rightLeft * deltaTime * cameraSpeed);
            break;
        }
}

void Camera::processMouseMovement(float xOffset, float yOffset){
    yaw += 0.5 * xOffset;
    pitch -= 0.5 * yOffset;
    if(pitch >= 89){
        pitch = 89;
    }else if(pitch <= -89){
        pitch = -89;
    }
    float radYaw = glm::radians(yaw);
    float radPitch = glm::radians(pitch);

    cameraDirection = glm::vec3(std::cos(radYaw) * std::cos(radPitch), std::sin(radPitch), std::sin(radYaw) * std::cos(radPitch));
}

void Camera::save(){
    resetPosition = cameraPosition;
    //resetDirection = cameraDirection;
}

void Camera::reset(){
    cameraPosition = resetPosition;
    //cameraDirection = resetDirection;
}

glm::mat4 Camera::getViewMatrix() const{
    return glm::lookAt(cameraPosition, cameraPosition + cameraDirection, worldUp);
}
