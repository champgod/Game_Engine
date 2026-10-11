#include "Mesh.h"

Mesh::Mesh(const float* vertices, GLsizei vertexCount){    
    this->vertexCount = vertexCount; // Sets the vertex count to whatever we pass

    glGenVertexArrays(1, &vao); // Generates a vertex array object names
    glGenBuffers(1, &vbo); // Generates buffer object names

    glBindVertexArray(vao); // Binds a vertex array object
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // Binds the named buffer objects

    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertexCount) * 3 * sizeof(float), vertices, GL_STATIC_DRAW); // configure buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr); //configure vertex attribute data

    glEnableVertexAttribArray(0); // enable vertex attribute data
}

Mesh::~Mesh(){
    if(vao != 0){
        glDeleteVertexArrays(1, &vao);
    }
    if(vbo != 0){
        glDeleteBuffers(1, &vbo);
    }
}

void Mesh::bind() const{
    glBindVertexArray(vao);
}

bool Mesh::isValid() const{
    return (vao != 0 && vbo != 0 && vertexCount > 0);
}

GLsizei Mesh::getVertexCount() const{
    return vertexCount;
}

