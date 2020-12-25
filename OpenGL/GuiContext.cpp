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
  //ShowMeshSelector(selectedEnt, fbo);
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiContext::StartFrame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  ImGui::Begin("Test");
}

void GuiContext::Render() {
  ImGui::End();
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

void GuiContext::ShowMeshSelector(DataFileHandler* loadedData, Camera* camera,
				  Renderer* renderer) {
  //std::vector<std::string> meshNames = e_handler->GetMeshNames();
  if(ImGui::CollapsingHeader("Add entity")) {
    for (int i=0; i<loadedData->NumMeshes(); i++) {
      ImGui::Selectable(loadedData->GetMeshName(i));
      if (ImGui::IsItemHovered()) {
	Debug::Instance().PrintError("Mesh called");
	unsigned int test = renderer->previewMesh(loadedData, camera, i);
	ImGui::SameLine();
	ImGui::Image((void*) test, ImVec2(400, 400));
      }
    }
  }
}
