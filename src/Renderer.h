#pragma once
#include <OpenGL/gl3.h>
#include "Mesh.h"
#include "ShaderProgram.h"

class Renderer {
    public:
        void render(const ShaderProgram& program, const Mesh& mesh) const;
};