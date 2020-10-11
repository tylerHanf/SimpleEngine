#pragma once

#include <vector>
#include "Entity.h"

class EntityHandler {
 public:
    void AddEntity(const char* objPath, glm::vec3 pos);
    Entity* GetEntity(unsigned int idx);
    int NumEntities(void);
    
 private:
    std::vector<Entity*> entities;
};
