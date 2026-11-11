#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Camera::Camera(glm::vec3 position, glm::vec3 direction){
    cameraPosition = position; // Sets a default camera position upon initialization
    cameraDirection = direction; // Sets a default camera direction upon initialization
    resetPosition = position; // Sets a default reset position to the position
    //resetDirection = direction;
}

/*getPosition returns the camera's position vector*/
glm::vec3 Camera::getPosition() const{
    return cameraPosition;
}

/*getDirection returns the camera's direction vector*/
glm::vec3 Camera::getDirection() const{
    return cameraDirection;
}

/*setPosition takes in a parameter vector position and sets the camera's position to it*/
void Camera::setPosition(glm::vec3 position){
    cameraPosition = position;
}

/*setDirection takes in a parameter vector direction and sets the camera's direction to it*/
void Camera::setDirection(glm::vec3 direction){ 
    cameraDirection = direction;
}

/*move takes in a parameter vector direction and a float deltaTime and moves the camera in the specified direction*/
void Camera::move(MovementDirection direction, float deltaTime){
    float cameraSpeed = 2.5f; // Sets the camera speed
    glm::vec3 frontBack = glm::normalize(cameraDirection); // faces forward (but we can subtract to move back)
    glm::vec3 rightLeft = glm::normalize(glm::cross(cameraDirection, worldUp)); //faces right (but we can subtract to move left)
    switch (direction) {
        case MovementDirection::Forward:
            cameraPosition += (frontBack * deltaTime * cameraSpeed); // Moves forward by unit vector in direction of camera over delta time with the camera speed
            break; 
        case MovementDirection::Backward:
            cameraPosition -= (frontBack * deltaTime * cameraSpeed); // Moves backward by unit vector in opposite direction of camera over delta time with camera speed
            break;

        case MovementDirection::Left:
            cameraPosition -= (rightLeft * deltaTime * cameraSpeed); // Moves left using frontBack which faces right by default, but we subtract to go left by camera speed amount over delta time
            break;

        case MovementDirection::Right:
            cameraPosition += (rightLeft * deltaTime * cameraSpeed); // Moves right using frontBack which faces right by default and we go by camera speed over delta time
            break;
        }
}

void Camera::processMouseMovement(float xOffset, float yOffset){
    yaw += 0.5 * xOffset; // We increase the yaw by xOffset amount
    pitch -= 0.5 * yOffset; // We increase the pitch by yOffset amount
    if(pitch >= 89){
        pitch = 89; // We lock the vertical camera motion to not exceed 89 degrees. 
    }else if(pitch <= -89){
        pitch = -89; // We lock the vertical camera motion to not exceed -89 degrees. 
    }
    float radYaw = glm::radians(yaw); 
    float radPitch = glm::radians(pitch);

    cameraDirection = glm::vec3(std::cos(radYaw) * std::cos(radPitch), std::sin(radPitch), std::sin(radYaw) * std::cos(radPitch));
}

void Camera::save(){
    resetPosition = cameraPosition; // Sets the reset position to wherever the camera currently is positioned
    //resetDirection = cameraDirection; 
}

void Camera::reset(){
    cameraPosition = resetPosition; // Sets the position of the camera to where we saved the previous camera position
    //cameraDirection = resetDirection;
}

glm::mat4 Camera::getViewMatrix() const{
    return glm::lookAt(cameraPosition, cameraPosition + cameraDirection, worldUp); 
}
