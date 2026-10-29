#pragma once
#include "Mesh.h"
#include "Transform.h"
#include "Material.h"

class GameObject{
    public:
        GameObject() = default;
        ~GameObject() = default;

        /*GETTERS*/
        const Mesh* getMesh() const;
        const Material* getMaterial() const;
        Transform getTransform() const;


    private:
        /*INSTANCE ATTRIBUTES*/
        const Mesh* mesh = nullptr;
        const Material* material = nullptr;
        Transform transform;
};