#include "Editor.h"
#include <chrono>
#include <thread>

Editor::Editor(Renderer* curRenderer) :
    camera(glm::vec3(0.0f, 0.0f, 0.0f))
{
    renderer = curRenderer;
}

void Editor::GetKeyInput(GLFWwindow* window, ModeHandler* curMode,
			 GL_Context* context) {
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
	curMode->SwitchMode(Mode(DEBUG));
	context->SetNoCursor();
	std::this_thread::sleep_for(std::chrono::milliseconds(30));
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
