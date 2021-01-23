#pragma once

#include <vector>
#include <stack>

#include "GL_Context.h"
//#include "GuiContext.h"
#include "Camera.h"
#include "ShaderHandler.h"
#include "EntityHandler.h"
#include "ModeHandler.h"
#include "MouseRay.h"
#include "DataFileHandler.h"
#include "ObjectHandles.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

/*
Handles all rendering operations
*/
class Renderer {
 public:
  Renderer(GL_Context* contextObj, ShaderHandler* shaders, ModeHandler* modeH);
  void DisplayDebug(EntityHandler* entities, Camera* camera);
  void DisplayEditor(EntityHandler* entities, Camera* camera, DataFileHandler* loadedData);
  void LoadData(DataFileHandler* meshes, Camera* camera);
  void InitializeFramebuffer(DataFileHandler* loadedData);
  void drawMeshPreviews(DataFileHandler* loadedData, Camera* camera);
  unsigned int previewMesh(DataFileHandler* loadedData, Camera* camera, int meshIndex);
  GLuint getVBOIdx(int idx);
  glm::mat4 getPmat(void);
  glm::mat4 getVmat(void);
  glm::mat4 getMmat(void);
  GLuint* getFramebuffer(int index);
  GLuint* getTextID(int idx);
  void clearFramebuffer();
  void DisplayObjectHandles(ObjectHandles* objectHandles,
			    Entity* currentEntity);
    
 private:
  std::vector<GLuint> vao, vbo;
  std::vector<unsigned int> textIDs;
  unsigned int fbo, renderTexture, renderbuffer;
  ShaderHandler* shaderHandler;
  ModeHandler* mode; 
  GLuint mvLoc, projLoc;
  glm::mat4 pMat, mMat, vMat;
  std::stack<glm::mat4> mvStack;
  float aspect;
  int width, height;
  GL_Context* context;

  //void drawColliders(std::vector<Collider*> showColliders, EntityHandler* entities);
};
