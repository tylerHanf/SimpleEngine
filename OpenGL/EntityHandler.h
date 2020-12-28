#pragma once

#include <vector>
#include "Entity.h"
#include "DataFileHandler.h"

class EntityHandler {
 public:
  EntityHandler(DataFileHandler* loadedData);
  void AddEntity(int meshID, glm::vec3 pos, glm::vec3 inMin, glm::vec3 inMax);
  void RemoveEntity(int meshID);
  Entity* GetEntity(unsigned int idx);
  int NumEntities(void);
    
 private:
  std::vector<Entity> entities;
};
