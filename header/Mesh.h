#pragma once
#include <OpenGL/gl3.h>

class Mesh {
    public:
        Mesh(const float* vertices, const unsigned int* indices, GLsizei vertexCount, GLsizei indexCount); // Create constructor
        ~Mesh(); // Create destructor

        Mesh(const Mesh&) = delete; // prevents copies of our Mesh object being made
        Mesh& operator=(const Mesh&) = delete; // same here but using the equals operator

        bool isValid() const;
        void bind() const;

        GLsizei getVertexCount() const;
        GLsizei getIndexCount() const;

    private:
        GLuint ibo = 0;
        GLuint vao = 0;
        GLuint vbo = 0;
        GLsizei vertexCount = 0;
        GLsizei indexCount = 0;
};