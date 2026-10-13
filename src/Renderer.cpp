#include "Renderer.h"

void Renderer::render(const ShaderProgram& program, const Mesh& mesh, const Transform& transform) const{
    program.use();
    //program.setVec3Uniform("uTranslation", transform.getX(), transform.getY(), transform.getZ());
    program.setMat4Uniform("uModel", transform.getModelMatrix());
    mesh.bind();
    glDrawArrays(GL_TRIANGLES, 0, mesh.getVertexCount());
}