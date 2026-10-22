#include "Renderer.h"

void Renderer::render(const ShaderProgram& program, const Mesh& mesh, const Transform& transform, const glm::mat4& projection, const Light& light, const Camera& camera, const Texture& texture) const{
    program.use();

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    program.setInt("uTexture", 0);

    program.setVec3Uniform("lightPos", light.getPosition());
    program.setVec3Uniform("lightColor", light.getColor());
    program.setVec3Uniform("objectColor", glm::vec3(1.0f, 0.2f, 0.2f));

    program.setMat4Uniform("uProjection", projection);
    program.setMat4Uniform("uView", camera.getViewMatrix());
    program.setMat4Uniform("uModel", transform.getModelMatrix());
    
    mesh.bind();
    glDrawArrays(GL_TRIANGLES, 0, mesh.getVertexCount());
}