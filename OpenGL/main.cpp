#include <vector>
#include <chrono>
#include <thread>
#include "Debug.h"

#include "Entity.h"
#include "GL_Context.h"
#include "Renderer.h"
#include "Camera.h"
#include "EntityHandler.h"
#include "ShaderHandler.h"
#include "ModeHandler.h"
#include "DataFileHandler.h"
#include "Editor.h"

const std::string WINDOW_NAME = std::string("Simple Engine");
const char* VERT_SHADER_PATH = "vertShader.glsl";
const char* FRAG_SHADER_PATH = "fragShader.glsl";
const char* VERT_LIGHT_SHADER_PATH = "basicLightVert.glsl";
const char* FRAG_LIGHT_SHADER_PATH = "basicLightFrag.glsl";
int width, height;

/*
Handles program initialization,
not context init
*/
void InitProgram(void) {
    width = 800;
    height = 800;
}

void resizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void GetKeyInput(GLFWwindow* window, Camera* camera, ModeHandler* mode,
		 GL_Context* context) {
    static double timePassed = 0;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
       camera->MoveForward();
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
	camera->MoveBack();
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
	camera->MoveRight();
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
	camera->MoveLeft();
    }

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
	mode->SwitchMode(Mode(EDITOR));
	context->SetCursor();
	std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void GetMouseInput(GLFWwindow* window, Camera* camera) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    camera->LookAround(xpos, ypos);
}

/*
TODOs:
setup per object translation functions
handle movement -> WIP
Fix screen size changing
Add debugging input features
Consider implementing scripting
    capabilities

Make a time class to handle delays and timing (not using GLFW timing)
*/
int main(int argc, char** argv) {
    EntityHandler e_handler;
    ShaderHandler s_handler;
    DataFileHandler filehandler = DataFileHandler(&e_handler, &s_handler); 
    
    ModeHandler mode = ModeHandler((const char**) argv, argc);
    InitProgram();
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, -8.0f));
    GL_Context curContext = GL_Context(width, height, WINDOW_NAME);
    
    s_handler.AddShader(VERT_SHADER_PATH, FRAG_SHADER_PATH);
    s_handler.AddShader(VERT_LIGHT_SHADER_PATH, FRAG_LIGHT_SHADER_PATH);
    Renderer renderer = Renderer(&curContext, &s_handler, &mode);
    Editor editor = Editor(&renderer);
   
    renderer.LoadData(&e_handler);
    curContext.ResizeCallback(&resizeCallback);
    glfwSetInputMode(curContext.getWindow(), GLFW_STICKY_KEYS, GLFW_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    s_handler.Use(1);
    //mode.SwitchMode(Mode(DEBUG));
    
    while(!curContext.ExitWindow()) {
	curContext.ClearColorBuffer();
	curContext.Poll();
	if (mode.CurMode() == Mode(DEBUG)) {
	    renderer.DisplayDebug(&e_handler, &camera);
	    GetKeyInput(curContext.getWindow(), &camera, &mode, &curContext);
	    GetMouseInput(curContext.getWindow(), &camera);
	}
		
	else if (mode.CurMode() == Mode(EDITOR)) {
	    renderer.DisplayEditor(&e_handler, editor.GetCamera());
	    editor.GetKeyInput(curContext.getWindow(), &mode, &curContext);
	}
	curContext.Swap();
    }
    
    curContext.Terminate();
    return 0;
}
