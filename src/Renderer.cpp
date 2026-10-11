#include "Renderer.h"

void Renderer::render(const ShaderProgram& program, const Mesh& mesh) const{
    program.use();
    mesh.bind();
    glDrawArrays(GL_TRIANGLES, 0, mesh.getVertexCount());
}