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

void GuiContext::RenderGui(MouseRay* pointer, EntityHandler* selectedEnt, GLuint* fbo) {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  ImGui::ShowDemoWindow();
  ShowMeshSelector(selectedEnt, fbo);
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiContext::handleCollider(Entity* selectedEnt) {
  if (selectedEnt->showingCollider()) {
    if (ImGui::Button("Hide collider"))
      selectedEnt->toggleCollider();
  }
  else if (ImGui::Button("Show collider"))
    selectedEnt->toggleCollider();
  
  ImGui::SameLine();
  if (ImGui::Button("Switch Collider Type"))
    selectedEnt->getCollider()->toggleShape();
}

void GuiContext::ShowMeshSelector(EntityHandler* e_handler, GLuint* fbo) {
  //std::vector<std::string> meshNames = e_handler->GetMeshNames();
  if(ImGui::CollapsingHeader("Add entity")) {
    for (int i=0; i<e_handler->NumMeshes(); i++) {
      ImGui::Selectable(e_handler->GetMeshName(i));
      if (ImGui::IsItemHovered()) {
	ImGui::SameLine();
	ImGui::Image((void*) *fbo, ImVec2(400, 400));
      }
    }
  }
}
