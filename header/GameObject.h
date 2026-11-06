#pragma once
#include "Mesh.h"
#include "Transform.h"
#include "Material.h"

class GameObject{
    public:
        /*CONSTRUCTOR*/
        GameObject(const Mesh* mesh, const Material* material, const Transform& transform);

        /*GETTERS*/
        const Mesh* getMesh() const;
        const Material* getMaterial() const;
        Transform& getTransform(); // We can modify this transform.
        const Transform& getTransform() const; // This one means we can't modify the transform and the returned transform is not modifiable

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