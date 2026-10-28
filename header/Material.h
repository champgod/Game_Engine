#pragma once

#include "Texture.h"
#include <glm/glm.hpp>


class Material{
    public: 
        /* CONSTRUCTOR AND DESTRUCTORS */
        Material() = default;
        ~Material() = default;

        /* GETTERS AND SETTERS DOWN HERE */
        const Texture* getTexture() const;
        glm::vec3 getColor() const;
        float getSpecularStrength() const;
        float getShininess() const;

        void setTexture(const Texture* texture); 
        void setColor(glm::vec3 color); 
        void setSpecularStrength(float specularStrength); 
        void setShininess(float shininess);

    private:
     /*INSTANCE VARIABLES OF MATERIAL*/
        const Texture* texture = nullptr; // materials usually have fixed texture
        glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f); // the original color of the material object
        float specularStrength = 0.5f;
        float shininess = 0.0f;

};