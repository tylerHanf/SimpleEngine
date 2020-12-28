#pragma once

#include <vector>
#include "Entity.h"
#include "DataFileHandler.h"

class EntityHandler {
 public:
  EntityHandler(DataFileHandler* loadedData);
  void AddEntity(int meshID, glm::vec3 pos);
  void RemoveEntity(int meshID);
  Entity* GetEntity(unsigned int idx);
  int NumEntities(void);
    
 private:
  std::vector<Entity> entities;
};
