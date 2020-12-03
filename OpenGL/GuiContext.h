#pragma once

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include "EntityHandler.h"
#include "MouseRay.h"

class GuiContext {
 public:
  GuiContext(GLFWwindow* window);
  void RenderGui(MouseRay* ray, EntityHandler* entities, glm::mat4 mMat);
  bool mouseInUse(void);
  
 private:
  ImGuiIO* io;
};
