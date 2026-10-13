#include "Transform.h"

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