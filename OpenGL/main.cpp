#include <vector>
#include "Debug.h"

#include "Entity.h"
#include "GL_Context.h"
#include "Renderer.h"
#include "Camera.h"

const std::string WINDOW_NAME = std::string("Simple Engine");
const char* VERT_SHADER_PATH = "vertShader.glsl";
const char* FRAG_SHADER_PATH = "fragShader.glsl";
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

/*
TODOs:
Add camera class
setup per object translation functions
handle movement
Consider implementing scripting
    capabilities
*/
int main(int argc, char** argv) {
    InitProgram();
    Mesh testMesh = Mesh("cube.obj");
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, -8.0f));
    GL_Context curContext = GL_Context(width, height, WINDOW_NAME);
    Renderer renderer = Renderer(VERT_SHADER_PATH, FRAG_SHADER_PATH, &curContext);
    
    std::vector<Entity*> entities;
    for (int i=0; i<10; i++) {
	Entity* newEntity = new Entity("Cube.obj", glm::vec3(8.0f, 0.0f, 0.0f));
	entities.push_back(newEntity);
    }
    
    renderer.LoadData(entities);
    curContext.ResizeCallback(&resizeCallback);

    while(!curContext.ExitWindow()) {
	curContext.ClearColorBuffer();
	renderer.Display(curContext.getWindow(), curContext.GetTime(),
			 entities, &camera);
	curContext.Swap();
	curContext.Poll();
	GetKeyInput(curContext.getWindow(), &camera);
    }

    curContext.Terminate();
    return 0;
}
