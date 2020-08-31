#include "Renderer.h"
#include "ShaderHandler.h"

Renderer::Renderer(const char* vPath, const char* fPath, int numVAOs, int numVBOs) {
    ShaderHandler sHandler;
    renderingProgram = sHandler.createShaderProgram(vPath, fPath);
    
}

void Renderer::Display(GLFWwindow* window, double currentTime) {
}
    
