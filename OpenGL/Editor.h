#pragma once

#include "Renderer.h"
#include "Camera.h"
#include "EntityHandler.h"
#include "ModeHandler.h"
#include "GuiContext.h"
#include "MouseRay.h"
#include <GLFW/glfw3.h>
#include <vector>

class Editor {
 public:
    Editor(Renderer* curRenderer, GLFWwindow* window, EntityHandler* entities);
    void GetKeyInput(GLFWwindow* window, ModeHandler* curMode, GL_Context* context);
    GuiContext* GetGuiContext(void);
    Camera* GetCamera(void);
    void drawBoundingBox(int entIdx, EntityHandler* ents, GL_Context* context,
		       ShaderHandler* s_handler);
  
    MouseRay* GetMouseRay(void);
    Entity* GetSelectedEntity(void);

 private:
  Renderer* renderer;
  EntityHandler* entities;
  GuiContext guiContext;
  Camera camera;
  MouseRay pointer;
  Entity* selectedEntity;
};
