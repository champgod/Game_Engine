#include "Light.h"

Light::Light(const glm::vec3 position, const glm::vec3 color){
    lightPosition = position;
    lightColor = color;
}

void Light::setPosition(glm::vec3 position){
    lightPosition = position;
}

void Light::setColor(glm::vec3 color){
    lightColor = color;
}

glm::vec3 Light::getPosition() const{
    return lightPosition;
}

glm::vec3 Light::getColor() const{
    return lightColor;
}