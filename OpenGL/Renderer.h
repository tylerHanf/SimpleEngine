#pragma once

#include <vector>
#include <stack>

#include "Entity.h"
#include "GL_Context.h"
#include "Camera.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

/*
Handles all rendering operations
*/
class Renderer {
 public:
    Renderer(GL_Context* contextObj, std::vector<GLuint> shaders);
    //Renderer(const char* vPath, const char* fPath, GL_Context* contextObj);
    void Display(GLFWwindow* window, double currentTime,
		 std::vector<Entity*> entities, Camera* camera);
    void LoadData(std::vector<Entity*> entities);
    
 private:
    //GLuint renderingProgram;
    std::vector<GLuint> vao, vbo;
    std::vector<GLuint> renderingPrograms;
    GLuint mvLoc, projLoc;
    glm::mat4 pMat, mMat, vMat, mvMat;
    std::stack<glm::mat4> mvStack;
    float aspect;
    int width, height;
    GL_Context* context;
};
