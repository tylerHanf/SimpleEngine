#pragma once

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include "EntityHandler.h"
#include "MouseRay.h"

class GuiContext {
 public:
  GuiContext(GLFWwindow* window);
  void RenderGui(MouseRay* ray, Entity* selectedEnt);
  void handleCollider(Entity* selectedEnt);
  bool mouseInUse(void);
  
 private:
  ImGuiIO* io;
};
