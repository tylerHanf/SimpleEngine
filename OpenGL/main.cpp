#include <vector>
#include "Debug.h"

#include "Entity.h"
#include "GL_Context.h"
#include "Renderer.h"

const std::string WINDOW_NAME = std::string("Simple Engine");
const char* VERT_SHADER_PATH = "vertShader.glsl";
const char* FRAG_SHADER_PATH = "fragShader.glsl";
int width, height;

/*
Handles program initialization,
not context init
*/
void InitProgram(void) {
    width = 640;
    height = 480;
}

int main(int argc, char** argv) {
    InitProgram();
    Mesh testMesh = Mesh("cube.obj");
    Entity firstEntity = Entity("cube.obj", glm::vec3(1.0f, 0.0f, 0.0f));
    GL_Context curContext = GL_Context(width, height, WINDOW_NAME);
    Renderer renderer = Renderer(VERT_SHADER_PATH, FRAG_SHADER_PATH, &curContext);

    std::vector<Entity*> entities;
    entities.push_back(&firstEntity);

    renderer.LoadData(entities);


    
    while(!curContext.ExitWindow()) {
	curContext.ClearColorBuffer();
	renderer.Display(curContext.getWindow(), curContext.GetTime(), entities);
	curContext.Swap();
	curContext.Poll();
    }

    //curContext.Terminate();
    //Debug::Instance().PrintError("Working");
    return 0;
}
