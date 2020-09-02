#pragma once

#include <string>
#include <iostream>
#include <GLEW/glew.h>

/*
Handles all shader reader and loading
*/
class ShaderHandler {
 public:
    GLuint createShaderProgram(const char* vertp, const char* fragp);
    
 private:
    std::string readShaderSource(const char* filepath);
    void printProgramLog(int prog);
    void printShaderLog(GLuint shader);
    bool checkOpenGLError(void);
};
