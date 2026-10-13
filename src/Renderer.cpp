#include "Renderer.h"

void Renderer::render(const ShaderProgram& program, const Mesh& mesh, const Transform& transform, const glm::mat4& projection) const{
    program.use();

    program.setMat4Uniform("uProjection", projection);
    program.setMat4Uniform("uModel", transform.getModelMatrix());
    mesh.bind();
    glDrawArrays(GL_TRIANGLES, 0, mesh.getVertexCount());
}