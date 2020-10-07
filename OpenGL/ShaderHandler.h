#pragma once

#include <string>
#include <iostream>
#include <GLEW/glew.h>
#include <GLM/glm.hpp>

struct B_Uniforms {
    GLuint model;
    GLuint view;
    GLuint projection;
    GLuint objColor;
};

struct L_Uniforms {
    GLuint lightPos;
    GLuint lightColor;
};

enum Uniform {
    MODEL,
    VIEW,
    PROJECTION,
    E_COLOR,
    L_POS,
    L_COLOR
};

/*
Handles all shader reader and loading
*/
class ShaderHandler {
 public:
    ShaderHandler(const char* vertp, const char* fragp);
    
    void SetMat4Uniform(Uniform loc, glm::mat4 val);
    void SetVec3Uniform(Uniform loc, glm::vec3 val);
    GLuint GetHandle(void);
    struct B_Uniforms basic;    
 private:
    GLuint handler;

    struct L_Uniforms light;
    
    void createShaderProgram(const char* vertp, const char* fragp);
    void setupUniforms(void);
    
    std::string readShaderSource(const char* filepath);
    void printShaderLog(GLuint shader);
    void printProgramLog(int prog);
    bool checkOpenGLError(void);
    void GL_SetMat4(GLuint loc, glm::mat4 val);
    void GL_SetVec3(GLuint loc, glm::vec3 val);
};
