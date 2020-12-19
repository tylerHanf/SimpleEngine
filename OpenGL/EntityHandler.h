#pragma once

#include <vector>
#include "Entity.h"
#include "DataFileHandler.h"

class EntityHandler {
 public:
  EntityHandler(DataFileHandler* loadedData);
  void AddEntity(int meshID, glm::vec3 pos);
  Entity* GetEntity(unsigned int idx);
  std::vector<float> GetMesh(int idx);
  int NumEntities(void);
  int NumMeshes(void);
  int NumTriangles(int meshIdx);
  const char* GetMeshName(int meshIdx);
  unsigned char* GetTexture(int meshIdx, int* width, int* height);
    
 private:
  std::vector<meshData> meshData; 
  std::vector<Entity*> entities;
};
