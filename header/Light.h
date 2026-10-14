#pragma once
#include <glm/glm.hpp>

class Light{
    public:

    Light(const glm::vec3 position, const glm::vec3 color);

    void setPosition(glm::vec3 position);
    void setColor(glm::vec3 color);

    glm::vec3 getPosition() const;
    glm::vec3 getColor() const;


    private:
        glm::vec3 lightPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 lightColor = glm::vec3(0.0f, 0.0f, 0.0f);

};