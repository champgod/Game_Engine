#include "GameObject.h"



const Mesh* GameObject::getMesh() const{
    return mesh;
}

const Material* GameObject::getMaterial() const{
    return material;
}

Transform GameObject::getTransform() const{
    return transform;
}