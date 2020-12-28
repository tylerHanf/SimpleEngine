#pragma once

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include "EntityHandler.h"
#include "MouseRay.h"
#include "Camera.h"
#include "Renderer.h"

class GuiContext {
 public:
  GuiContext(GLFWwindow* window);
  void ShowMeshSelector(DataFileHandler* loadedData, Camera* camera,
			Renderer* renderer, EntityHandler* e_handler);
  void handleCollider(Entity* selectedEnt);
  bool mouseInUse(void);
  void StartFrame();
  void Render();
  
 private:
  ImGuiIO* io;
};
