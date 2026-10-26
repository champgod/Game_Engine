#pragma once
#include "Texture.h"

class Material{
    public: 
        const Texture texture; // materials usually have fixed texture
        const glm::vec3 


        Texture getTexture() const; // but to access the texture itself

};