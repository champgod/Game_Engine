#include "Renderer.h"

void Renderer::render(const ShaderProgram& program, const glm::mat4& projection, const Light& light, const Camera& camera, const GameObject& object) const{
    const Mesh& mesh = *object.getMesh(); 
    const Material& material = *object.getMaterial();
    const Transform& transform = object.getTransform();

    program.use();
    glActiveTexture(GL_TEXTURE0);
    material.getTexture()->bind(); // Binds the material.

    program.setInt("uTexture", 0);

    program.setVec3Uniform("lightPos", light.getPosition());
    program.setVec3Uniform("lightColor", light.getColor());
    program.setVec3Uniform("objectColor", glm::vec3(1.0f, 0.2f, 0.2f));

    program.setVec3Uniform("cameraPos", camera.getPosition());
    program.setFloat("specularStrength", material.getSpecularStrength()); // Sets the specular strength to whatever the material's specular strength is
    program.setFloat("shininess", material.getShininess()); // Sets the shininess to whatever the material's shininess is

    program.setMat4Uniform("uProjection", projection);
    program.setMat4Uniform("uView", camera.getViewMatrix());
    program.setMat4Uniform("uModel", transform.getModelMatrix()); // Sets the uModel to the transform model matrix
    
    mesh.bind();
    glDrawArrays(GL_TRIANGLES, 0, mesh.getVertexCount()); // Draws the arrays using the vertex count in Mesh
}