#include "GameObject.h"

const Mesh* GameObject::getMesh() const{
    return mesh;
}

const Material* GameObject::getMaterial() const{
    return material;
}

Transform& GameObject::getTransform(){
    return transform;
}

const Transform& GameObject::getTransform() const{
    return transform;
}

void GameObject::setMesh(const Mesh* mesh){
    this->mesh = mesh;
}

void GameObject::setMaterial(const Material* material){
    this->material = material;
}