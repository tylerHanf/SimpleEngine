#pragma once

#include <vector>
#include <GL/glew.h>

/*
Handles all rendering operations
*/
class Renderer {
 public:
    Renderer();
    void Display(GLFWwindow* window, double currentTime);

 private:
    GLuint renderingProgram;
    vector<GLuint> vao, vbo;
    GLuint mvLoc, projLoc;
    int numVAOs, numVBOs;
    glm::mat4 pMat, mMat, vMat, mvMat;
    glm::stack<glm::mat4> mvStack;
};
