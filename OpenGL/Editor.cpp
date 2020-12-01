#include "Editor.h"
#include "Debug.h"

/*
TODO: FIX BOX COLLIDER PARAMS
*/
Editor::Editor(Renderer* curRenderer, GLFWwindow* window, EntityHandler* curEntities) :
  camera(glm::vec3(0.0f, 0.0f, 0.0f)),
  guiContext(window)
{
    renderer = curRenderer;
    entities = curEntities;
    pointer = MouseRay();
}

void Editor::GetKeyInput(GLFWwindow* window, ModeHandler* curMode,
			 GL_Context* context) {
  int state;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    camera.MoveForward();
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    camera.MoveBack();
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    camera.MoveRight();
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    camera.MoveLeft();
  }
  
  state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
  if (state == GLFW_PRESS) {
    GetMouseMove(window);
  }
  
  if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
    if (curMode->CanSwitch(context->GetTime())) {
      curMode->SwitchMode(Mode(DEBUG), context->GetTime());
      context->SetNoCursor();
    }
  }

  state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  if (state == GLFW_PRESS && not guiContext.mouseInUse()) {
    GetMouseSelect(window);
  }
}

void Editor::GetMouseMove(GLFWwindow* window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    camera.LookAround(xpos, ypos);
}

void Editor::GetMouseSelect(GLFWwindow* window) {
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  glm::mat4 pMat = renderer->getPmat();
  glm::mat4 vMat = renderer->getVmat();

  /*
  for (unsigned int i=0; i<entities->NumEntities(); i++) {
    Entity* curEnt = entities->GetEntity(i);
    if (curEnt->getBoxCollider()->isPicked(xpos, ypos, 1000, 1000, pMat, vMat)) {
      glm::vec3 pos = curEnt->getLocation();
      
      Debug::Instance().PrintError(pos.x);
      Debug::Instance().PrintError(pos.y);
      Debug::Instance().PrintError(pos.z);
      
    }
  }
  */
  Entity* picked = pointer.pointingAt();
  if (picked != NULL) {
    Debug::Instance().PrintError("picked");
  }
}

Camera* Editor::GetCamera(void) {
    return &camera;
}

GuiContext* Editor::GetGuiContext(void) {
  return &guiContext;
}


