#include "Transform.h"

void Transform::translate(float dx, float dy, float dz){
    posX += dx;
    posY += dy;
    posZ += dz;
}

void Transform::rotate(float radX, float radY, float radZ){
    this->radX = radX;
    this->radY = radY;
    this->radZ = radZ;
}

