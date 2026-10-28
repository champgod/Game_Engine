#pragma once
#include <OpenGL/gl3.h>
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Light.h"
#include "Camera.h"
#include "Texture.h"
#include "Material.h"
#include <glm/glm.hpp>


class Renderer {
    public:
        void render(const ShaderProgram& program, const Mesh& mesh, const Transform& transform, 
            const glm::mat4& projection, const Light& light, const Camera& camera, const Texture& texture, 
        const Material& material) const;
};