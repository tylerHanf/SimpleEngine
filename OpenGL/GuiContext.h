#pragma once

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

class GuiContext {
 public:
  GuiContext(GLFWwindow* window);
  void RenderGui(void);
  bool mouseInUse(void);
  
 private:
  ImGuiIO* io;
};
