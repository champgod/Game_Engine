#pragma once
#include <OpenGL/gl3.h>

class ShaderProgram{
    // It's easy to paste code and not understand it so I want to be able to link where I'm finding these methods that I'm using
    // This OpenGL stuff is quite complicated though. 

    public:
        ShaderProgram(const char* vertexSource, const char* fragmentSource); // Constructor for shader program taking in a vertex and fragment source
        ~ShaderProgram(); // Destructor for shader program

        ShaderProgram(const ShaderProgram&) = delete; // prevents copies of our shader object being made
        ShaderProgram& operator=(const ShaderProgram&) = delete; // same here but using the equals operator

        bool isValid() const; // checks that the program is valid
        void use() const; // method call that makes it so we use the program as needed

        void setVec3Uniform(const char* name, float x, float y, float z) const;

    private:
        GLuint programId = 0; // each program has a unique identifier
        static GLuint compileShader(GLenum type, const char* source); // this will be helpful

};