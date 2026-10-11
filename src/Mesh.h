#pragma once
#include <OpenGL/gl3.h>

class Mesh {
    public:
        Mesh(const float* vertices, GLsizei vertexCount); // Create constructor
        ~Mesh(); // Create destructor

        Mesh(const Mesh&) = delete; // prevents copies of our Mesh object being made
        Mesh& operator=(const Mesh&) = delete; // same here but using the equals operator

        bool isValid() const;
        void bind() const;
        GLsizei getVertexCount() const;

    private:
        GLuint vao = 0;
        GLuint vbo = 0;
        GLsizei vertexCount = 0;
};