#include <vector>
#include "Debug.h"

#include "Entity.h"
#include "GL_Context.h"
#include "Renderer.h"
#include "Camera.h"
#include "ShaderHandler.h"
#include "ModeHandler.h"
#include "EntityFileHandler.h"

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

void GetKeyInput(GLFWwindow* window, Camera* camera) {
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
*/
int main(int argc, char** argv) {
    std::vector<Entity*> entities;
    EntityFileHandler filehandler;
    
    filehandler.LoadEntities(entities);
    
    //ModeHandler mode = ModeHandler((const char**) argv);
    InitProgram();
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, -8.0f));
    GL_Context curContext = GL_Context(width, height, WINDOW_NAME);
    ShaderHandler baseHandler(VERT_SHADER_PATH, FRAG_SHADER_PATH);
    ShaderHandler lightHandler(VERT_LIGHT_SHADER_PATH, FRAG_LIGHT_SHADER_PATH);
    std::vector<ShaderHandler*> shaders;
    shaders.push_back(&baseHandler);
    shaders.push_back(&lightHandler);
    Renderer renderer = Renderer(&curContext, shaders);

    //    std::vector<Entity*> entities;
    //Entity* House = new Entity("house.obj", glm::vec3(8.0f, 0.0f, 0.0f), Entity_Type(WORLD_OBJ));
    //entities.push_back(House);
    renderer.LoadData(entities);
    curContext.ResizeCallback(&resizeCallback);
    curContext.SetInputMode();
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    while(!curContext.ExitWindow()) {
	curContext.ClearColorBuffer();
	renderer.Display(curContext.getWindow(), curContext.GetTime(),
			 entities, &camera);
	curContext.Swap();
	curContext.Poll();
	GetKeyInput(curContext.getWindow(), &camera);
	GetMouseInput(curContext.getWindow(), &camera);
    }

    curContext.Terminate();
    return 0;
}
