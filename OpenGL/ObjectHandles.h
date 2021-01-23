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
  
 private:
  HandleType handleType = HandleType::MOVE;
  int currentVBO;
  Entity handleMeshes[3];
  int moveBaseIndex;
};
