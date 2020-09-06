#include "Renderer.h"
#include "ShaderHandler.h"
#include "Debug.h"

/*
Renderer constructor, also makes rendering program
Must be called after GL_Context obj is made
*/
Renderer::Renderer(const char* vPath, const char* fPath, GL_Context* contextObj) {
    ShaderHandler sHandler;
    width, height = 0;
    context = contextObj;
    renderingProgram = sHandler.createShaderProgram(vPath, fPath);
}

/*
Loads vertices into GPU from entity objects
 */
void Renderer::LoadData(std::vector<Entity*> entities) {
    //Note the number of VAOs, just for initial build
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
	glBufferData(GL_ARRAY_BUFFER, entities[i]->numMeshVertices(),
		     entities[i]->getMeshVertices(), GL_STATIC_DRAW); 
    }
}

/*
Main display function
*/
void Renderer::Display(GLFWwindow* window, double currentTime,
		       std::vector<Entity> entities) {
    context->ClearDepthBuffer();
    context->ClearColorBuffer();
    
    mvLoc = context->GetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = context->GetUniformLocation(renderingProgram, "proj_matrix");

    context->GetFrameBufferSize(&width, &height);
    aspect = (float)width/(float)height;

    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
    //TODO: Make camera Object and define lookat object
    vMat = glm::lookAt(glm::vec3(0.0f, 1.0f*5.0, 20.0f), glm::vec3(3.0f, 2.0f, -8.0f),
		       glm::vec3(0.0f, 1.0f, 0.0f));
    mvStack.push(vMat);
    
    Debug::Instance().PrintError(std::to_string(entities.size()));
    
    for (int i=0; i<entities.size(); i++) {
	mvStack.push(mvStack.top());
	context->SetMatrix4fv(projLoc, pMat);
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	context->SetMatrix4fv(mvLoc, mvStack.top());
	glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, entities[i].numMeshVertices()/3);
	mvStack.pop();
    }
    mvStack.pop();
}
    
