#ifndef SHADER_PROGRAM_H

#define SHADER_PROGRAM_H

#include <glad/glad.h>
#include <iostream>
#include <vector>

class ShaderProgram {
   private:
    GLuint programId;
    std::vector<GLuint> shaders;
    void deleteShaders();

   public:
    bool addShader(GLuint, const GLchar *shaderContent);
    bool link();
    void use();
    void unbind();
    void destroy();
    ShaderProgram();
    ~ShaderProgram();
};

#endif