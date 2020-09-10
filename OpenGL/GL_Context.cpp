#include "GL_Context.h"
#include "Debug.h"

/*
GL_Context constructor
Takes window name, width of screen, height of screen
*/
GL_Context::GL_Context(int width, int height, const std::string windowName) {
    window = NULL;
    if (!Init(width, height, windowName)) {
	return;
    }
}

/*
Clears color buffer
*/
void GL_Context::ClearColorBuffer(void) {
    glClear(GL_COLOR_BUFFER_BIT);
}

/*
Clears depth buffer bit
*/
void GL_Context::ClearDepthBuffer(void) {
    glClear(GL_DEPTH_BUFFER_BIT);
}

/*
Use specified rendering program
*/
void GL_Context::UseProgram(GLuint renderingProgram) {
    glUseProgram(renderingProgram);
}

/*
Get a uniform variable location
*/
GLuint GL_Context::GetUniformLocation(GLuint renderingProgram, const char* varname) {
    return glGetUniformLocation(renderingProgram, varname);
}

/*
Get the current size of the frame buffer
*/
void GL_Context::GetFrameBufferSize(int* width, int* height) {
    glfwGetFramebufferSize(window, width, height);
}
    

/*
Swap current buffer with back buffer
*/
void GL_Context::Swap(void) {
    glfwSwapBuffers(window);
}

/*
Poll for new events
*/
void GL_Context::Poll(void) {
    glfwPollEvents();
}

/*
Kills glfw instance and frees memory
*/
void GL_Context::Terminate(void) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

/*
Get the current window
*/
GLFWwindow* GL_Context::getWindow(void) {
    return window;
}

/*
Determines if user has closed window via glfwWindowShouldClose()
*/
bool GL_Context::ExitWindow(void) {
    return glfwWindowShouldClose(window);
}

/*
Sets a 4x4 Matrix Uniform var in GPU
*/
void GL_Context::SetMatrix4fv(GLuint varLoc, glm::mat4 value) {
    glUniformMatrix4fv(varLoc, 1, GL_FALSE,  glm::value_ptr(value));
}

/*
Get current time
*/
double GL_Context::GetTime(void) {
    return glfwGetTime();
}

/*
Sets the window resize callback function
*/
void GL_Context::ResizeCallback(GLFWwindowsizefun function) {
    glfwSetWindowSizeCallback(window, function);
}

/*
Sets the key input callback
*/
void GL_Context::SetKeyCallback(GLFWkeyfun function) {
    glfwSetKeyCallback(window, function);
}

/*
Inits GLFW and GLEW
*/
bool GL_Context::Init(int width, int height, const std::string windowName) {
    if (!glfwInit()) {
	Debug::Instance().PrintError("ERROR: Failed to initialize GLFW.");
	return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

    if (!window) {
	Debug::Instance().PrintError("ERROR: Failed to make Window.");
	glfwTerminate();
	return false;
    }

    glfwMakeContextCurrent(window);
    
    if (glewInit() != GLEW_OK) {
	Debug::Instance().PrintError("ERROR: Failed to initialize GLEW.");
	return false;
    }

    glfwSwapInterval(1);
    return true;
}
