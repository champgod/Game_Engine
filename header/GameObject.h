#pragma once

class GameObject{
    public:
        const Mesh* getMesh() const;
        const Material* getMaterial() const;

    private:
        const Mesh* mesh = nullptr;
        const Material* material = nullptr;
        Transform transform;
};