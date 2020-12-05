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

void GuiContext::RenderGui(MouseRay* pointer, EntityHandler* entities, glm::mat4 mMat) {
  Entity* firstEnt = entities->GetEntity(0);
  Entity* secondEnt = entities->GetEntity(1);
  glm::vec3 origin = pointer->getOrigin();
  glm::vec3 direction = pointer->getDirection();
  glm::vec3 loc0 = firstEnt->getLocation();
  glm::vec3 loc1 = secondEnt->getLocation();
  glm::vec4 worldSpace0 = mMat * glm::vec4(loc0.x, loc0.y, loc0.z, 1.0);
  glm::vec4 worldSpace1 = mMat * glm::vec4(loc1.x, loc1.y, loc1.z, 1.0);
  
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::Begin("Data");
  ImGui::Text("Mouse Origin: <%f, %f, %f>", origin.x, origin.y, origin.z);
  ImGui::Text("Mouse Direction: <%f, %f, %f>", direction.x, direction.y, direction.z);
  ImGui::Text("Entity 0 worldspace: <%f, %f, %f>", worldSpace0.x, worldSpace0.y, worldSpace0.z);
  ImGui::Text("Entity 1 worldspace: <%f, %f, %f>", worldSpace1.x, worldSpace1.y, worldSpace1.z);
  ImGui::End();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
