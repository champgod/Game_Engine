#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

void Transform::translate(float dx, float dy, float dz){
    posX += dx;
    posY += dy;
    posZ += dz;
}

void Transform::rotate(float radX, float radY, float radZ){
    this->radX += radX;
    this->radY += radY;
    this->radZ += radZ;
}

void Transform::setPosition(float posX, float posY, float posZ){
    this->posX = posX;
    this->posY = posY;
    this->posZ = posZ;
}

void Transform::setRotation(float radX, float radY, float radZ){
    this->radX = radX;
    this->radY = radY;
    this->radZ = radZ;
}

void Transform::setScale(float scaleX, float scaleY, float scaleZ){
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->scaleZ = scaleZ;
}

float Transform::getX() const{
    return posX;
}

float Transform::getY() const{
    return posY;
}

float Transform::getZ() const{
    return posZ;
}

float Transform::getRadX() const{
    return radX;
}

float Transform::getRadY() const{
    return radY;
}

float Transform::getRadZ() const{
    return radZ;
}

float Transform::getScaleX() const{
    return scaleX;
}

float Transform::getScaleY() const{
    return scaleY;
}

float Transform::getScaleZ() const{
    return scaleZ;
}

glm::mat4 Transform::getModelMatrix() const{
    glm::mat4 model(1.0f); // This creates a identity matrix (just diagonal of 1s)

    model = glm::translate(model, glm::vec3(posX, posY, posZ)); // for translations
    model = glm::rotate(model, radZ, glm::vec3(0.0f, 0.0f, 1.0f)); // for rotation about z axis
    model = glm::rotate(model, radY, glm::vec3(0.0f, 1.0f, 0.0f)); // for rotation about y axis
    model = glm::rotate(model, radX, glm::vec3(1.0f, 0.0f, 0.0f)); // for rotation about x axis
    model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ)); // for scaling

    //order in which operations are done matters

    return model;
}