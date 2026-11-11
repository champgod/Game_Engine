#include "Mesh.h"

Mesh::Mesh(const float* vertices, const unsigned int* indices, GLsizei vertexCount, GLsizei indexCount){    
    this->vertexCount = vertexCount; // Sets the vertex count to whatever we pass
    this->indexCount = indexCount;

    glGenVertexArrays(1, &vao); // Generates a vertex array object names
    glBindVertexArray(vao); // Binds a vertex array object

    glGenBuffers(1, &vbo); // Generates buffer object names
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // Binds the named buffer objects
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertexCount) * 8 * sizeof(float), vertices, GL_STATIC_DRAW); // configure buffer data

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr); //configure vertex attribute data

    glGenBuffers(1, &ibo); // Generates index buffer object names
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // Binds the named index buffer objects
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indexCount) * sizeof(unsigned int), indices, GL_STATIC_DRAW); // configure index buffer data

    glEnableVertexAttribArray(0); // enable vertex attribute data

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float))); // this allows for us to get surface normals, which tell us how much light is reflected off of a surface 
    glEnableVertexAttribArray(1); 

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

Mesh::~Mesh(){
    if(ibo != 0){
        glDeleteBuffers(1, &ibo);
    }
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
    return (vao != 0 && vbo != 0  &&ibo != 0 && vertexCount > 0 && indexCount > 0);
}

GLsizei Mesh::getVertexCount() const{
    return vertexCount;
}

GLsizei Mesh::getIndexCount() const{
    return indexCount;
}


