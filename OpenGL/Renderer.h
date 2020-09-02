#pragma once

#include <vector>
#include <stack>

#include "Entity.h"
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

/*
Handles all rendering operations
*/
class Renderer {
 public:
    Renderer(const char* vPath, const char* fPath);
    void Display(GLFWwindow* window, double currentTime);
    void LoadData(std::vector<Entity*> entities);
    
 private:
    GLuint renderingProgram;
    std::vector<GLuint> vao, vbo;
    GLuint mvLoc, projLoc;
    glm::mat4 pMat, mMat, vMat, mvMat;
    std::stack<glm::mat4> mvStack;
    float aspect;
    int width, height;
};
