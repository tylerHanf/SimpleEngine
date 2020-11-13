#pragma once

#include <vector>
#include <stack>

#include "GL_Context.h"
#include "GuiContext.h"
#include "Camera.h"
#include "ShaderHandler.h"
#include "EntityHandler.h"
#include "ModeHandler.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

/*
Handles all rendering operations
*/
class Renderer {
 public:
    Renderer(GL_Context* contextObj, ShaderHandler* shaders, ModeHandler* modeH);
    void DisplayDebug(EntityHandler* entities, Camera* camera);
    void DisplayEditor(EntityHandler* entities, Camera* camera, GuiContext* gContext);
    void LoadData(EntityHandler* e_handler);
    
 private:
    std::vector<GLuint> vao, vbo;
    ShaderHandler* shaderHandler;
    ModeHandler* mode; 
    GLuint mvLoc, projLoc;
    glm::mat4 pMat, mMat, vMat;
    std::stack<glm::mat4> mvStack;
    float aspect;
    int width, height;
    GL_Context* context;
};
