#include "headers/ShaderProgram.hpp"

ShaderProgram::ShaderProgram() {
    this->shaders = std::vector<GLuint>();
}

ShaderProgram::~ShaderProgram() {
}

bool ShaderProgram::addShader(GLuint type, const GLchar *shaderContent) {
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &shaderContent, NULL);
    glCompileShader(shader);

    int success;
    char log[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, log);
        std::cout << log << std::endl;
        return false;
    }

    this->shaders.push_back(shader);
    return true;
}

bool ShaderProgram::link() {
    this->programId = glCreateProgram();

    for (int i = 0; i < this->shaders.size(); i++) {
        glAttachShader(this->programId, this->shaders[i]);
    }

    glLinkProgram(this->programId);

    int success;
    char log[1024];

    glGetProgramiv(this->programId, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(this->programId, 1024, NULL, log);
        std::cout << log << std::endl;
        return false;
    }

    this->deleteShaders();

    this->shaders.clear();

    return true;
}

void ShaderProgram::unbind() {
    glUseProgram(GL_FALSE);
}

void ShaderProgram::use() {
    glUseProgram(this->programId);
}

void ShaderProgram::deleteShaders() {
    for (int i = 0; i < this->shaders.size(); i++) {
        glDeleteShader(this->shaders[i]);
    }
    this->shaders.clear();
}

void ShaderProgram::destroy() {
    if (this->programId) {
        glDeleteProgram(this->programId);
    }

    if (this->shaders.size() > 0) {
        this->deleteShaders();
    }
}