#include "Editor.h"
#include "Debug.h"

/*
TODO: FIX BOX COLLIDER PARAMS
*/
Editor::Editor(Renderer* curRenderer, GLFWwindow* window, EntityHandler* curEntities,
	       DataFileHandler* dataHandler) :
  camera(glm::vec3(0.0f, 0.0f, 0.0f), 2.0f),
  guiContext(window),
  objectHandles(dataHandler)
{
    renderer = curRenderer;
    entities = curEntities;
    pointer = MouseRay();
}

void Editor::GetKeyInput(GLFWwindow* window, ModeHandler* curMode,
			 GL_Context* context) {
  int state;  
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  
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

  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    camera.setSpeed(0.2);
  }
  
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
    camera.setSpeed(2.0);
  }
  
  state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
  if (state == GLFW_PRESS) {
    camera.LookAround(xpos, ypos);    
  }
  
  if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
    if (curMode->CanSwitch(context->GetTime())) {
      curMode->SwitchMode(Mode(DEBUG), context->GetTime());
      context->SetNoCursor();
    }
  }

  state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  if (state == GLFW_PRESS && not guiContext.mouseInUse()) {
    glm::mat4 pMat = renderer->getPmat();
    glm::mat4 vMat = renderer->getVmat();
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    pointer.Update(xpos, ypos, width, height, pMat, vMat, camera.getPosition());      
    int picked = pointer.pointingAt(entities);


    if (picked != -1) {
      selectedEntity = entities->GetEntity(picked);
    }
    else selectedEntity = 0;
  }
}

MouseRay* Editor::GetMouseRay(void) {
  return &pointer;
}

GuiContext* Editor::GetGuiContext(void) {
  return &guiContext;
}

Camera* Editor::GetCamera(void) {
  return &camera;
}

Entity* Editor::GetSelectedEntity(void) {
  if (selectedEntity) {
    return selectedEntity;
  }
  return NULL;
}

ObjectHandles* Editor::GetObjectHandles(void) {
  return &objectHandles;
}

