#include "Editor.h"
#include "Debug.h"

Editor::Editor(Renderer* curRenderer, GLFWwindow* window) :
  camera(glm::vec3(0.0f, 0.0f, 0.0f)),
  guiContext(window)
{
    renderer = curRenderer;  
  
}

void Editor::GetKeyInput(GLFWwindow* window, ModeHandler* curMode,
			 GL_Context* context) {
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

  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    GetMouseMove(window);
  }
  
  if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
    if (curMode->CanSwitch(context->GetTime())) {
      curMode->SwitchMode(Mode(DEBUG), context->GetTime());
      context->SetNoCursor();
    }
  }

  int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  if (state == GLFW_PRESS && not guiContext.mouseInUse()) {
    Debug::Instance().PrintError("Left clicked");
  }
}

void Editor::GetMouseMove(GLFWwindow* window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    camera.LookAround(xpos, ypos);
}

void Editor::GetMouseSelect(GLFWwindow* window) {

}

Camera* Editor::GetCamera(void) {
    return &camera;
}

GuiContext* Editor::GetGuiContext(void) {
  return &guiContext;
}
