#include <vector>

#include "Mesh.h"
#include "Entity.h"
#include "GL_Context.h"

const std::string WINDOW_NAME = std::string("Simple Engine");
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
    
    GL_Context curContext = GL_Context(width, height, WINDOW_NAME);

    while(!curContext.ExitWindow()) {
	curContext.Clear();
	curContext.Swap();
	curContext.Poll();
    }

    curContext.Terminate();
    return 0;
}
