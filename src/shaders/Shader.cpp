#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"

Shader::Shader() {}

Shader& Shader::add(GLenum type, std::string filename) {
    std::string str = readShader(filename);
    const GLchar* shaderCode = str.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);
    
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        compilationErrors(shader);
        exit(EXIT_FAILURE);
    }
    
    shaders.push_back(shader);
    
    return *this;
}

std::string Shader::readShader(std::string filename) {
    std::ifstream ifs(filename, std::ifstream::in);
    
    if (!ifs) {
        std::cerr << "Unable to Open File " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
    
    std::stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();

    return ss.str();
}

void Shader::link() {
    program = glCreateProgram();
    
    for (GLuint shader : shaders) {
        glAttachShader(program, shader);
    }
    glLinkProgram(program);
    
    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        linkageErrors();
        exit(EXIT_FAILURE);
    }
}

void Shader::use() {
    glUseProgram(program);
}

void Shader::compilationErrors(GLint shader) {
    GLint length;
    
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    GLchar* log = new GLchar[length + 1];
    
    glGetShaderInfoLog(shader, length, &length, log);
    std::cout << "Compile Error, Log Below" << std::endl
              << log << std::endl;
    
    delete[] log;
}

void Shader::linkageErrors() {
    GLint length;
    
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
    GLchar* log = new GLchar[length + 1];
    
    glGetProgramInfoLog(program, length, &length, log);
    std::cout << "Compile Error, Log Below" << std::endl
         << log << std::endl;
    
    delete[] log;
}

GLuint Shader::uniformLocation(std::string uniformName) {
    return glGetUniformLocation(program, uniformName.c_str());
}

void Shader::setUniform(GLuint id, GLuint value) {
    glUniform1i(id, value);
}

void Shader::setUniform(GLuint id, GLfloat value) {
    glUniform1f(id, value);
}

void Shader::setUniform(GLuint id, glm::vec3 value) {
    glUniform3fv(id, 1, glm::value_ptr(value));
}

void Shader::setUniform(GLuint id, glm::mat3 value) {
    glUniformMatrix3fv(id, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniform(GLuint id, glm::mat4 value) {
    glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(value));
}
