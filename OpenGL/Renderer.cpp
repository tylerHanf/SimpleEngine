#include "Renderer.h"
#include "Debug.h"
#include "ShaderHandler.h"

/*
Renderer constructor, also makes rendering program
Must be called after GL_Context obj is made
*/
Renderer::Renderer(GL_Context* contextObj, std::vector<GLuint> shaders) {
    //ShaderHandler sHandler;
    width, height = 0;
    context = contextObj;
    //GLuint renderingProgram = sHandler.createShaderProgram(vPath, fPath);
    //renderingPrograms.push_back(renderingProgram);
    renderingPrograms = shaders;
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
    
    glGenVertexArrays(numVAOs, (GLuint*)&vao[0]);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, (GLuint*)&vbo[0]);
    
    //Assume each entity only has one mesh
    for (int i=0; i < entities.size(); i++) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
	glBufferData(GL_ARRAY_BUFFER, entities[i]->numMeshVertices()*sizeof(float),
		     entities[i]->getMeshVertices(), GL_STATIC_DRAW);
    }
}

/*
Main display function
*/
void Renderer::Display(GLFWwindow* window, double currentTime,
		       std::vector<Entity*> entities, Camera* camera) {
    context->ClearDepthBuffer();
    context->ClearColorBuffer();
    context->UseProgram(renderingPrograms[0]);
    
    mvLoc = context->GetUniformLocation(renderingPrograms[0], "mv_matrix");
    projLoc = context->GetUniformLocation(renderingPrograms[0], "proj_matrix");

    context->GetFrameBufferSize(&width, &height);
    aspect = (float)width/(float)height;

    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
    //TODO: Make camera Object and define lookat object
    vMat = glm::lookAt(camera->getPosition(), camera->GetLookAt(),
		       camera->GetUp());
    
    context->SetMatrix4fv(projLoc, pMat);
    mvStack.push(vMat);

    for (int i=0; i<entities.size(); i++) {
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(8.0f, 0.0f, 1.0f));

	/*
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime*5,
				     glm::vec3(0.0f, 2.0f, 0.0f));
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime,
				     glm::vec3(2.0f, 0.0f, 0.0f));
	*/
	context->SetMatrix4fv(mvLoc, mvStack.top());
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, entities[i]->numMeshVertices()/3);
	mvStack.pop(); mvStack.pop();
    }
}
