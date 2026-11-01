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
        Transform& getTransform();

        /*SETTERS*/
        void setMesh(const Mesh* mesh);
        void setMaterial(const Material* material);

        //no setter for Transform. why? because transform methods work for all gameobjects 

    private:
        /*INSTANCE ATTRIBUTES*/
        const Mesh* mesh = nullptr;
        const Material* material = nullptr;
        Transform transform;
};