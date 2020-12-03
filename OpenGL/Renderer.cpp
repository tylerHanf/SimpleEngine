#include "Renderer.h"
#include "Debug.h"

/*
Renderer constructor, also makes rendering program
Must be called after GL_Context obj is made
*/
Renderer::Renderer(GL_Context* contextObj, ShaderHandler* shaders, ModeHandler* modeH) {
    width, height = 0;
    context = contextObj;
    shaderHandler = shaders;
    mode = modeH;
}

/*
Loads vertices into GPU from entity objects
 */
void Renderer::LoadData(EntityHandler* entities) {
    //Note the number of VAOs, just for initial build
    int numEnts = entities->NumEntities();
    int numVAOs = 1;
    int numVBOs = numEnts;
    Entity* curEnt = NULL;

    vao.resize(numVAOs);
    vbo.resize(numVBOs);
    
    glGenVertexArrays(numVAOs, (GLuint*)&vao[0]);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, (GLuint*)&vbo[0]);
    
    //Assume each entity only has one mesh
    for (unsigned int i=0; i < numEnts; i++) {
	curEnt = entities->GetEntity(i);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
	glBufferData(GL_ARRAY_BUFFER, curEnt->numMeshVertices()*sizeof(float),
		     curEnt->getMeshVertices(), GL_STATIC_DRAW);
    }
}

GLuint Renderer::getVBOIdx(int idx) {
  return vbo[idx];
}

glm::mat4 Renderer::getPmat(void) {
  return pMat;
}

glm::mat4 Renderer::getVmat(void) {
  return vMat;
}

glm::mat4 Renderer::getMmat(void) {
  return mMat;
}

/*
Main display function
*/
void Renderer::DisplayDebug(EntityHandler* entities, Camera* camera) {
    context->ClearDepthBuffer();
    context->ClearColorBuffer();
    shaderHandler->Use(1);
    context->UseProgram(shaderHandler->GetCurProg());
    
    context->GetFrameBufferSize(&width, &height);
    aspect = (float)width/(float)height;

    pMat = glm::perspective(1.0472f, aspect, 0.1f, 2000.0f);
    vMat = glm::lookAt(camera->getPosition(), camera->GetLookAt(),
		       camera->GetUp());
    
    shaderHandler->SetMat4Uniform(Uniform(PROJECTION), pMat);
    shaderHandler->SetMat4Uniform(Uniform(VIEW), vMat);
    shaderHandler->SetVec3Uniform(Uniform(E_COLOR), glm::vec3(0.9f, 0.8f, 0.9f));
    shaderHandler->SetVec3Uniform(Uniform(L_POS), glm::vec3(2.0f, 20.0f, 1.0f));
    shaderHandler->SetVec3Uniform(Uniform(L_COLOR), glm::vec3(1.0f, 1.0f, 0.80f));
    
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(8.0f, 0.0f, 1.0f));
    mvStack.push(mMat);

    int numEnts = entities->NumEntities();
    for (int i=0; i<numEnts; i++) {
        Entity* curEntity = entities->GetEntity(i);      
	mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), curEntity->getLocation());	
	shaderHandler->SetMat4Uniform(Uniform(MODEL), mvStack.top());
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (const void*)12);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, entities->GetEntity(i)->numMeshVertices()/3);

	mvStack.pop();
    }
    mvStack.pop();
}

void Renderer::DisplayEditor(EntityHandler* entities, Camera* camera, GuiContext* gContext) {
    context->ClearDepthBuffer();
    context->ClearColorBuffer();
    shaderHandler->Use(1);
    context->UseProgram(shaderHandler->GetCurProg());
    
    context->GetFrameBufferSize(&width, &height);
    aspect = (float)width/(float)height;

    pMat = glm::perspective(1.0472f, aspect, 0.1f, 2000.0f);
    vMat = glm::lookAt(camera->getPosition(), camera->GetLookAt(),
		       camera->GetUp());
    
    shaderHandler->SetMat4Uniform(Uniform(PROJECTION), pMat);
    shaderHandler->SetMat4Uniform(Uniform(VIEW), vMat);
    shaderHandler->SetVec3Uniform(Uniform(E_COLOR), glm::vec3(0.9f, 0.8f, 0.9f));
    shaderHandler->SetVec3Uniform(Uniform(L_POS), glm::vec3(2.0f, 20.0f, 1.0f));
    shaderHandler->SetVec3Uniform(Uniform(L_COLOR), glm::vec3(1.0f, 1.0f, 0.80f));
    
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    mvStack.push(mMat);

    int numEnts = entities->NumEntities();
    for (int i=0; i<numEnts; i++) {
        Entity* curEntity = entities->GetEntity(i);
        mvStack.push(mvStack.top());
	mvStack.top() *= glm::translate(glm::mat4(1.0f), curEntity->getLocation());
	shaderHandler->SetMat4Uniform(Uniform(MODEL), mvStack.top());
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (const void*)12);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, entities->GetEntity(i)->numMeshVertices()/3);

	mvStack.pop();
    }
    mvStack.pop();

    drawCollider(entities->GetEntity(1));
    
    //gContext->RenderGui();
}

void Renderer::drawCollider(Entity* entity) {
  // Draw line
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(2);
  
  shaderHandler->Use(2);
  context->UseProgram(shaderHandler->GetCurProg());
  
  shaderHandler->SetMat4Uniform(Uniform(PROJECTION), pMat);
  shaderHandler->SetMat4Uniform(Uniform(VIEW), vMat);
  shaderHandler->SetVec3Uniform(Uniform(E_COLOR), glm::vec3(0.9f, 0.8f, 0.9f));
  shaderHandler->SetVec3Uniform(Uniform(L_POS), glm::vec3(2.0f, 20.0f, 1.0f));
  shaderHandler->SetVec3Uniform(Uniform(L_COLOR), glm::vec3(1.0f, 1.0f, 0.80f));
    
  mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
  mMat *= entity->getBoxCollider()->getTransform();
  mMat *= glm::translate(glm::mat4(1.0f), entity->getLocation());

  shaderHandler->SetMat4Uniform(Uniform(MODEL), mMat);

  glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (const void*)12);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glDrawArrays(GL_TRIANGLES, 0, entity->numMeshVertices()/3);

  // Draw fill (normal)
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
  

