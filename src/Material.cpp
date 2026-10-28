#include "Material.h"

const Texture* Material::getTexture() const{
    return texture;
}

glm::vec3 Material::getColor() const{
    return color;
}

float Material::getSpecularStrength() const{
    return specularStrength;
}
float Material::getShininess() const{
    return shininess;
}

void Material::setTexture(const Texture* texture){
    this->texture = texture;
}

void Material::setColor(glm::vec3 color){
    this->color = color;
}

void Material::setSpecularStrength(float specularStrength){
    this->specularStrength = specularStrength;
} 

void Material::setShininess(float shininess){
    this->shininess = shininess;
}
