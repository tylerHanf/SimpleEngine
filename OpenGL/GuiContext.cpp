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

void GuiContext::StartFrame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  ImGui::Begin("Mesh Selector");
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
				  Renderer* renderer, EntityHandler* e_handler) {
  if(ImGui::CollapsingHeader("Add entity")) {
    for (int i=0; i<loadedData->NumMeshes(); i++) {
      if(ImGui::Selectable(loadedData->GetMeshName(i))) {
	e_handler->AddEntity(i, camera->GetLookAt()-glm::vec3(0.0f, 5.0f, -10.0f));
	ImGui::GetMousePos();
      }
      if (ImGui::IsItemHovered()) {
	unsigned int textureID = renderer->previewMesh(loadedData, camera, i);
	int windowWidth = ImGui::GetWindowWidth();
	int windowHeight = ImGui::GetWindowHeight();
	ImGui::SetNextWindowPos(ImVec2(windowWidth, 0));
	ImGui::Begin("Mesh Preview");
	ImGui::SameLine();
	ImGui::Image((void*) textureID, ImVec2(400, 400));
	ImGui::End();
      }
    }
  }
}
