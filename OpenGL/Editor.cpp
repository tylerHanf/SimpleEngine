#include "Editor.h"
#include "Debug.h"

Editor::Editor(Renderer* curRenderer) :
    camera(glm::vec3(0.0f, 0.0f, 0.0f))
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
    GetMouseInput(window);
  }
  
  if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
    if (curMode->CanSwitch(context->GetTime())) {
      curMode->SwitchMode(Mode(DEBUG), context->GetTime());
      context->SetNoCursor();
    }
  }
}

void Editor::GetMouseInput(GLFWwindow* window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    camera.LookAround(xpos, ypos);
}

Camera* Editor::GetCamera(void) {
    return &camera;
}
