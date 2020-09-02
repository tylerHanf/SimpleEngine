#include "Renderer.h"
#include "ShaderHandler.h"

Renderer::Renderer(const char* vPath, const char* fPath) {
    ShaderHandler sHandler;
    renderingProgram = sHandler.createShaderProgram(vPath, fPath);
}

void Renderer::LoadData(std::vector<Entity*> entities) {
    int numVAOs = 1;
    int numVBOs = entities.size();
    vao.resize(numVAOs);
    vbo.resize(numVBOs);
    
    glGenVertexArrays(numVAOs, (GLuint*)&vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, (GLuint*)&vbo);

    //Assume each entity only has one mesh
    for (int i=0; i < entities.size(); i++) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
	glBufferData(GL_ARRAY_BUFFER, entities[i]->getMesh()->getVertices().size(),
		     entities[i]->getMesh()->getVertices(), GL_STATIC_DRAW); 
    }
}

void Renderer::Display(GLFWwindow* window, double currentTime, std::vector<Entity> entities) {
    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
    
}
    
