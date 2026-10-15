#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 direction){
    cameraPosition = position; //sets camera position
    cameraDirection = direction; //sets camera direction
    resetPosition = position; //sets the reset position as where the camera is initially created
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

void Camera::reset(){
    cameraPosition = resetPosition;
}

glm::mat4 Camera::getViewMatrix() const{
    return glm::lookAt(cameraPosition, cameraPosition + cameraDirection, worldUp);
}
