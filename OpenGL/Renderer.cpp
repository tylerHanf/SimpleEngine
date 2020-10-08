#include "Renderer.h"
#include "Debug.h"

/*
Renderer constructor, also makes rendering program
Must be called after GL_Context obj is made
*/
Renderer::Renderer(GL_Context* contextObj, std::vector<ShaderHandler*> &shaders) :
    renderingPrograms(shaders)
{
    width, height = 0;
    context = contextObj;
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
void Renderer::Display(std::vector<Entity*> entities, Camera* camera) {
    context->ClearDepthBuffer();
    context->ClearColorBuffer();
    context->UseProgram(renderingPrograms[1]->GetHandle());
    
    context->GetFrameBufferSize(&width, &height);
    aspect = (float)width/(float)height;

    pMat = glm::perspective(1.0472f, aspect, 0.1f, 2000.0f);
    vMat = glm::lookAt(camera->getPosition(), camera->GetLookAt(),
		       camera->GetUp());
    
    renderingPrograms[1]->SetMat4Uniform(Uniform(PROJECTION), pMat);
    renderingPrograms[1]->SetMat4Uniform(Uniform(VIEW), vMat);
    renderingPrograms[1]->SetVec3Uniform(Uniform(E_COLOR), glm::vec3(0.9f, 0.8f, 0.9f));
    renderingPrograms[1]->SetVec3Uniform(Uniform(L_POS), glm::vec3(2.0f, 20.0f, 1.0f));
    renderingPrograms[1]->SetVec3Uniform(Uniform(L_COLOR), glm::vec3(1.0f, 1.0f, 0.80f));
    
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(8.0f, 0.0f, 1.0f));
    mvStack.push(mMat);

    for (int i=0; i<entities.size(); i++) {
	mvStack.push(mvStack.top());
	renderingPrograms[1]->SetMat4Uniform(Uniform(MODEL), mvStack.top());

	glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (const void*)12);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, entities[i]->numMeshVertices()/3);

	mvStack.pop(); mvStack.pop();
    }
}
