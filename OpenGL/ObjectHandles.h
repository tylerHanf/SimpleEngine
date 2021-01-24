#pragma once

#include "DataFileHandler.h"
#include "Entity.h"

enum HandleType {
  MOVE,
  ROTATE,
  SCALE
};

class ObjectHandles {
 public:
  ObjectHandles(DataFileHandler* dataHandler);
  float getSize(void);
  int getVBOIdx(void);
  int numTriangles(void);
  void switchMode(HandleType newMode);
  int handleSelected(glm::vec3 origin, glm::vec3 ray);
  glm::vec3 getLocation(void);
  void updateLocation(glm::vec3 location);
  void bindObject(Entity* selectedEntity);
  glm::mat4 getTransform(int transformIdx);
  
 private:
  HandleType handleType = HandleType::MOVE;
  int currentVBO;
  float height;
  Entity handleMeshes[3];
  // array of transforms 
  glm::mat4 transforms[3];
  int moveBaseIndex;
};
