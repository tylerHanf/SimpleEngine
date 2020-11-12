#pragma once

#include "Renderer.h"
#include "Camera.h"
#include "EntityHandler.h"
#include "ModeHandler.h"
#include <GLFW/glfw3.h>

class Editor {
 public:
    Editor(Renderer* curRenderer);
    void GetKeyInput(GLFWwindow* window, ModeHandler* curMode, GL_Context* context);
    void GetMouseMove(GLFWwindow* window);
    void GetMouseSelect(GLFWwindow* window);
    Camera* GetCamera(void);

 private:
    Renderer* renderer;
    Camera camera;
};
