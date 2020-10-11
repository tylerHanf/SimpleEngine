#pragma once

#include <string>
#include <GLEW/glew.h>
#include <GLM/glm.hpp>

enum S_Type {
    BASIC,
    LIGHT
};

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

class Shader {
 public:
    Shader(const char* vertp, const char* fragp, S_Type i_type);
    S_Type getType(void);
    void SetMat4Uniform(Uniform loc, glm::mat4 val);
    void SetVec3Uniform(Uniform loc, glm::vec3 val);
    GLuint GetHandle(void);
    
 private:
    GLuint handler;
    struct L_Uniforms light;
    struct B_Uniforms basic;
    S_Type type;
    
    void createShaderProgram(const char* vertp, const char* fragp);
    void setupUniforms(void);
    
    std::string readShaderSource(const char* filepath);
    void printShaderLog(GLuint shader);
    void printProgramLog(int prog);
    bool checkOpenGLError(void);
    inline void GL_SetMat4(GLuint loc, glm::mat4 val);
    inline void GL_SetVec3(GLuint loc, glm::vec3 val);
    
    
    
};
