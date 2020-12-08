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

void GuiContext::RenderGui(MouseRay* pointer, Entity* selectedEnt) {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  if (selectedEnt != NULL) {
    glm::vec3 entityLoc = selectedEnt->getLocation();
    ImGui::Begin("Entity Properties");
    ImGui::Text("Position worldspace: <%f, %f, %f>", entityLoc.x, entityLoc.y, entityLoc.z);
    if (selectedEnt->canCollide()) {
      if(ImGui::CollapsingHeader("Collider Properties"))
	handleCollider(selectedEnt);
    }
    else {
     if (ImGui::Button("Add Collider"))
       selectedEnt->addCollider();
    }
    ImGui::End();
  }
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
