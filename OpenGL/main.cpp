#include <vector>
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
const char* VERT_COLLIDER_SHADER_PATH = "ColliderVert.glsl";
const char* FRAG_COLLIDER_SHADER_PATH = "ColliderFrag.glsl";
const char* VERT_GUI_SHADER_PATH = "GuiVertShader.glsl";
const char* FRAG_GUI_SHADER_PATH = "GuiFragShader.glsl";
const char* VERT_OBJECT_HANDLER_SHADER_PATH = "vertObjectHandler.glsl";
const char* FRAG_OBJECT_HANDLER_SHADER_PATH = "fragObjectHandler.glsl";
int width, height;

/*
 Handles program initialization,
 not context init
*/
void InitProgram(void) {
    width = 1000;
    height = 1000;
}

/*
 Handles window resizing
*/
void resizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

/*
 Key input for debug mode
*/
void GetKeyInput(GLFWwindow* window, Camera* camera, ModeHandler* mode,
		 GL_Context* context) {
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
      if (mode->CanSwitch(context->GetTime())) {
	mode->SwitchMode(Mode(EDITOR), context->GetTime());
	context->SetCursor();
      }
    }
}

/*
 Debug mouse input 
*/
void GetMouseInput(GLFWwindow* window, Camera* camera) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    camera->LookAround(xpos, ypos);
}

/*
 TODOs:

 --Priority--
 TOP: DATA-ORIENTED DESIGN
 1. get box colliders working
 2. decide on handling different colliders (may put off)
 3. start integrating textures
 4. make scripts for automating listing updates
 5. add model editing features
 6. check if bounding boxes are OBB and not AABB
 7. add easy editing features (like toggling rendering colliders)
 8. Multithread collision detection

 --Casual--
 consider making debug mode a class
 setup per object transform functions within class
 **handle movement
 add debugging input features--?
 make release version (or consider how to handle it)
 look through for optimizations
 think about custom space collider for hinckley

 ** = in good shape for now
*/

int main(int argc, char** argv) {
    ShaderHandler s_handler;
    ModeHandler mode = ModeHandler((const char**) argv, argc);
    InitProgram();
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f));
    GL_Context curContext = GL_Context(width, height, WINDOW_NAME);
    DataFileHandler dataHandler;
    EntityHandler e_handler(&dataHandler);    
    
    s_handler.AddShader(VERT_SHADER_PATH, FRAG_SHADER_PATH);
    s_handler.AddShader(VERT_LIGHT_SHADER_PATH, FRAG_LIGHT_SHADER_PATH);
    s_handler.AddShader(VERT_COLLIDER_SHADER_PATH, FRAG_COLLIDER_SHADER_PATH);
    s_handler.AddShader(VERT_OBJECT_HANDLER_SHADER_PATH, FRAG_OBJECT_HANDLER_SHADER_PATH);
    Renderer renderer = Renderer(&curContext, &s_handler, &mode);
    Editor editor = Editor(&renderer, curContext.getWindow(), &e_handler, &dataHandler);
    GuiContext* guiContext = editor.GetGuiContext();

    renderer.LoadData(&dataHandler, &camera);

    curContext.ResizeCallback(&resizeCallback);
    glfwSetInputMode(curContext.getWindow(), GLFW_STICKY_KEYS, GLFW_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
    while(!curContext.ExitWindow()) {
        curContext.Swap();
	curContext.Poll();	  	
        /*if (mode.CurMode() == Mode(DEBUG)) {
	    renderer.DisplayDebug(&e_handler, &camera);
	    GetKeyInput(curContext.getWindow(), &camera, &mode, &curContext);
	    GetMouseInput(curContext.getWindow(), &camera);
	}
	*/
	
	//else if (mode.CurMode() == Mode(EDITOR)) {

	//renderer.DisplayEditor(&e_handler, editor.GetCamera(), editor.GetGuiContext());
	//Test for drawing validly
	renderer.DisplayEditor(&e_handler, editor.GetCamera(), &dataHandler);

	//Gui render
	editor.GetKeyInput(curContext.getWindow(), &mode, &curContext);
	guiContext->StartFrame();
	guiContext->ShowMeshSelector(&dataHandler, editor.GetCamera(),
				     &renderer, &e_handler);
	
	if (editor.GetSelectedEntity()) {
	  guiContext->ShowEntityProperties(&e_handler, &dataHandler,
					   editor.GetSelectedEntity());
	  renderer.DisplayObjectHandles(editor.GetObjectHandles(),
					editor.GetSelectedEntity());
	}
		
	guiContext->Render();
	renderer.clearFramebuffer();
    }
    
    curContext.Terminate();
    return 0;
}
