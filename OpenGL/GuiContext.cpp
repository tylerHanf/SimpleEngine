#include "GuiContext.h"
#include <GLEW/glew.h>

GuiContext::GuiContext(GLFWwindow* window) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io_t = ImGui::GetIO();
  io = &io_t;
  (void)io;

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
  ImGui::StyleColorsDark();
}

bool GuiContext::mouseInUse() {
  return ImGui::GetIO().WantCaptureMouse;
}

void GuiContext::RenderGui() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::Begin("Editor");
  ImGui::Button("Test");
  ImGui::End();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
