#include "GameObject.h"

GameObject::GameObject(const Mesh* mesh, const Material* material, const Transform& transform){
    this->mesh = mesh;
    this->material = material;
    this->transform = transform;
}

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