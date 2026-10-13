#include "ShaderProgram.h"
#include <SDL3/SDL.h>
#include <glm/gtc/type_ptr.hpp>



GLuint ShaderProgram::compileShader(GLenum type, const char* source){ // Compiling shader
    /* Here we create a shader, give it source information, then compile and return the identifier */
    GLuint shader = glCreateShader(type); // creates the shader
    if (shader == 0){
        SDL_Log("Couldn't create a shader!");
        return 0; // Couldn't create a shader.
    }
    glShaderSource(shader, 1, &source, nullptr); // fills the shader with source information
    glCompileShader(shader); // compiles the shader

    GLint status = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if(status != GL_TRUE){ // Means that we couldn't compile the shader whatsoever

        char log[1024] = {}; // debug recommendations from ChatGPT

        glGetShaderInfoLog(shader, sizeof(log), nullptr, log); //debug recommendations from ChatGPT
        SDL_Log("Shader compilation failed: %s", log); //debug recommendations from ChatGPT
        glDeleteShader(shader); // deletes the shader

        return 0; // Signifies the shader compilation has failed
    }
    return shader; // Returns the shader value
}

ShaderProgram::ShaderProgram(const char* vertexSource, const char* fragmentSource){
    /* Here is the full implementation for the ShaderProgram constructor. Here we take in 2 parameters, vertexSource and fragmentSource.
    vertexSource will be responsible for containing all the information that we need to draw. On the other hand, fragmentSource is responsible
    for making it possible to decide what kind of colors that we would like to associate with whatever it is we're drawing. */

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource); // this should compile a shader for vertex source 
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource); // this should compile a shader for fragment source and return a gluint

    if (vertexShader == 0 || fragmentShader == 0){  // We check that both shaders are indeed existing
        if (vertexShader != 0){
            glDeleteShader(vertexShader);
        }
        if (fragmentShader != 0){
            glDeleteShader(fragmentShader);
        }
        return; // end the constructor early because one of the shaders did not compile
    }

    programId = glCreateProgram();
    if(programId == 0) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        SDL_Log("Program creation failed!");
        return; // Program creation failed
    }

    glAttachShader(programId, vertexShader); // attach vertex shader
    glAttachShader(programId, fragmentShader); // attach fragment shader

    glBindAttribLocation(programId, 0, "aPosition"); // Binds attribute location
    glBindFragDataLocation(programId, 0, "outColor"); // Binds color location
    glLinkProgram(programId); // Links the program

    GLint status = GL_FALSE; 
    glGetProgramiv(programId, GL_LINK_STATUS, &status);

    if(status != GL_TRUE){
        char log[1024] = {}; // debug recommendations from ChatGPT

        glGetProgramInfoLog(programId, sizeof(log), nullptr, log); //debug recommendations from ChatGPT
        SDL_Log("Linking failed: %s", log); //debug recommendations from ChatGPT

        glDeleteShader(vertexShader); // delete vertex shader
        glDeleteShader(fragmentShader); // delete fragment shader
        glDeleteProgram(programId); // delete the program
        programId = 0;

        return; // Linking failed
    }
    glDeleteShader(vertexShader); // delete vertex shader
    glDeleteShader(fragmentShader); // delete fragment shader
}

ShaderProgram::~ShaderProgram(){ // deletes the program to free memory
    if(isValid()){
        glDeleteProgram(programId);
    }
}

bool ShaderProgram::isValid() const{ // if our programId is not zero then we know the program exists and we return that 
    return (programId != 0);
}

void ShaderProgram::use() const{ // we use our program if it exists
    if(isValid()){
        glUseProgram(programId);
    }
}

/*
void ShaderProgram::setVec3Uniform(const char* name, float x, float y, float z) const{
    GLint uniformPos = glGetUniformLocation(programId, name);
    if(uniformPos != -1){
        glUniform3f(uniformPos, x, y, z);
    }else{
        SDL_Log("Uniform was not found!");
    }
}
    */

void ShaderProgram::setMat4Uniform(const char* name, const glm::mat4& matrix) const{
    GLint uniformPos = glGetUniformLocation(programId, name); 
    if(uniformPos != -1){
        glUniformMatrix4fv(uniformPos, 1, GL_FALSE, glm::value_ptr(matrix));
    }else{
        SDL_Log("Uniform matrix was not found!");
    }
}