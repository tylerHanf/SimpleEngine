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
void Renderer::LoadData(DataFileHandler* meshes, Camera* camera) {
  //Note the number of VAOs, just for initial build
  int numMeshes = meshes->NumMeshes();
  int numTexts = meshes->NumTextures() + 1;
  int numVAOs = 1;
  int numVBOs = numMeshes;
  meshData* curMesh;
    
  vao.resize(numVAOs);
  vbo.resize(numVBOs);
  fbo.resize(numVBOs);
  textIDs.resize(numTexts);
    
  glGenVertexArrays(numVAOs, (GLuint*)&vao[0]);
  //glGenFramebuffers(numVBOs, (GLuint*)&fbo[0]);
  glGenBuffers(numVBOs, (GLuint*)&vbo[0]);
  glGenTextures(numTexts, (GLuint*)&textIDs[0]);
  glBindVertexArray(vao[0]);

  glBindTexture(GL_TEXTURE_2D, textIDs[0]);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1000, 1000, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textIDs[0]);

  //Assume each entity only has one mesh
  int j = 1; // counter for textures
  for (int i=0; i < numMeshes; i++) {
    curMesh = meshes->GetMesh(i);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
    glBufferData(GL_ARRAY_BUFFER, curMesh->vertData.size()*sizeof(float),
		 (const void*) &(curMesh->vertData[0]), GL_STATIC_DRAW);
    if (curMesh->textData) {
      glBindTexture(GL_TEXTURE_2D, textIDs[j]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, curMesh->textWidth,
		   curMesh->textHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, curMesh->textData);

      glGenerateMipmap(GL_TEXTURE_2D);
      meshes->SetTextID(i, j);
      j++;
    }
  }
  InitializeFramebuffer();
}

void Renderer::InitializeFramebuffer() {
  //Debug::Instance().PrintError(width);
  //Debug::Instance().PrintError(height);
  glGenFramebuffers(1, &testFbo);
  glBindFramebuffer(GL_FRAMEBUFFER, testFbo);
  glGenTextures(1, &renderedTexture);

  glBindTexture(GL_TEXTURE_2D, renderedTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1000, 1000, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTexture, 0);  

  //render buffer
  glGenRenderbuffers(1, &depthrenderbuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1000, 1000);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    Debug::Instance().PrintError("Failed to create framebuffer");
  }
  
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

GLuint* Renderer::getFramebuffer(int index) {
  return &testFbo;
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
    vMat = glm::lookAt(camera->getPosition(), camera->GetLookAt(), camera->GetUp());
    
    shaderHandler->SetMat4Uniform(Uniform(PROJECTION), pMat);
    shaderHandler->SetMat4Uniform(Uniform(VIEW), vMat);
    shaderHandler->SetVec3Uniform(Uniform(E_COLOR), glm::vec3(0.9f, 0.8f, 0.9f));
    shaderHandler->SetVec3Uniform(Uniform(L_POS), glm::vec3(2.0f, 20.0f, 1.0f));
    shaderHandler->SetVec3Uniform(Uniform(L_COLOR), glm::vec3(1.0f, 1.0f, 0.80f));
    
    mvStack.push(glm::mat4(1.0));

    int numEnts = entities->NumEntities();
    int meshIdx;
    for (int i=0; i<numEnts; i++) {
        Entity* curEntity = entities->GetEntity(i);
	meshIdx = curEntity->getMeshIdx();
	mvStack.push(mvStack.top());
	mvStack.top() *= curEntity->getTransform();	
	shaderHandler->SetMat4Uniform(Uniform(MODEL), mvStack.top());
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, (const void*)12);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 32, (const void*)24);	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, entities->NumTriangles(meshIdx));

	mvStack.pop();
    }
    mvStack.pop();
}

void Renderer::DisplayEditor(EntityHandler* entities, Camera* camera, GuiContext* gContext) {
  std::vector<Collider*> showColliders;
  context->ClearDepthBuffer();
  context->ClearColorBuffer();
  shaderHandler->Use(0);
  context->UseProgram(shaderHandler->GetCurProg());

  context->GetFrameBufferSize(&width, &height);
  aspect = (float)width/(float)height;

  pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
  vMat = glm::lookAt(camera->getPosition(), camera->GetLookAt(),
		     camera->GetUp());
    
  shaderHandler->SetMat4Uniform(Uniform(PROJECTION), pMat);
  shaderHandler->SetMat4Uniform(Uniform(VIEW), vMat);
  shaderHandler->SetVec3Uniform(Uniform(E_COLOR), glm::vec3(0.9f, 0.8f, 0.9f));
  shaderHandler->SetVec3Uniform(Uniform(L_POS), glm::vec3(2.0f, 20.0f, 1.0f));
  shaderHandler->SetVec3Uniform(Uniform(L_COLOR), glm::vec3(1.0f, 1.0f, 0.80f));
    
  mvStack.push(glm::mat4(1.0));

  int numEnts = 0;
  int meshIdx;
  for (int i=0; i<numEnts; i++) {
    Entity* curEntity = entities->GetEntity(i);
    meshIdx = curEntity->getMeshIdx();
    /*if (curEntity->showingCollider()) {
      showColliders.push_back(curEntity->getCollider());
      }*/
    mvStack.push(mvStack.top());
    mvStack.top() *= curEntity->getTransform();
    shaderHandler->SetMat4Uniform(Uniform(MODEL), mvStack.top());    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
    //glBindBuffer(GL_FRAMEBUFFER, fbo[0]); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, (const void*)12);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 32, (const void*)24);	
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, entities->NumTriangles(meshIdx));
    mvStack.pop();
  }
  mvStack.pop();

    //drawColliders(showColliders, entities);
}

void Renderer::drawMeshPreviews(DataFileHandler* loadedData, Camera* camera, bool renderToFBO) {
  if (renderToFBO) {
    glBindFramebuffer(GL_FRAMEBUFFER, testFbo);
    glViewport(0,0,240,240);
  }
  context->ClearDepthBuffer();
  context->ClearColorBuffer();
  shaderHandler->Use(0);
  context->UseProgram(shaderHandler->GetCurProg());

  context->GetFrameBufferSize(&width, &height);
  if (!renderToFBO)
    glViewport(0,0,width, height);
  aspect = (float)width/(float)height;

  pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
  vMat = glm::lookAt(camera->getPosition(), camera->GetLookAt(),
		     camera->GetUp());
  
  shaderHandler->SetMat4Uniform(Uniform(PROJECTION), pMat);
  shaderHandler->SetMat4Uniform(Uniform(VIEW), vMat);
  shaderHandler->SetVec3Uniform(Uniform(E_COLOR), glm::vec3(0.9f, 0.8f, 0.9f));
  shaderHandler->SetVec3Uniform(Uniform(L_POS), glm::vec3(2.0f, 20.0f, 1.0f));
  shaderHandler->SetVec3Uniform(Uniform(L_COLOR), glm::vec3(1.0f, 1.0f, 0.80f));
  

  shaderHandler->SetMat4Uniform(Uniform(MODEL), glm::translate(glm::mat4(1.0), glm::vec3(1.0, 2.0, 0.0)));
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glBindBuffer(GL_FRAMEBUFFER, fbo[0]); 
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, (const void*)12);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 32, (const void*)24);	
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textIDs[loadedData->GetMesh(0)->textID]);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glDrawArrays(GL_TRIANGLES, 0, loadedData->GetMesh(0)->vertData.size());
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/*
void Renderer::drawColliders(std::vector<Collider*> showColliders, EntityHandler* entities) {
    // draw colliders
    int meshID;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2);
    shaderHandler->Use(2);
    context->UseProgram(shaderHandler->GetCurProg());
    shaderHandler->SetMat4Uniform(Uniform(PROJECTION), pMat);
    shaderHandler->SetMat4Uniform(Uniform(VIEW), vMat);
    for (auto collider : showColliders) {
      meshID = collider->getEntityID();
      mMat = collider->getTransform();
      shaderHandler->SetMat4Uniform(Uniform(MODEL), mMat);
      glBindBuffer(GL_ARRAY_BUFFER, vbo[meshID]);  
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, 0);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (const void*)12);
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glEnable(GL_DEPTH_TEST);
      glDepthFunc(GL_LEQUAL);
      glDrawArrays(GL_TRIANGLES, 0, entities->GetEntity(meshID)->numMeshVertices()/3);      
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }*/


  

