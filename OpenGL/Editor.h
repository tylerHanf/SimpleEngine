#pragma once

#include "Renderer.h"
#include "Camera.h"
#include "EntityHandler.h"
#include "ModeHandler.h"
#include "GuiContext.h"
#include <GLFW/glfw3.h>

class Editor {
 public:
    Editor(Renderer* curRenderer, GLFWwindow* window);
    void GetKeyInput(GLFWwindow* window, ModeHandler* curMode, GL_Context* context);
    void GetMouseMove(GLFWwindow* window);
    void GetMouseSelect(GLFWwindow* window);
    GuiContext* GetGuiContext(void);
    Camera* GetCamera(void);

 private:
    Renderer* renderer;
    GuiContext guiContext;
    Camera camera;
};
