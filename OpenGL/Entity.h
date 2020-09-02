#pragma once

#include "Mesh.h"
#include <GLM/glm.hpp>

class Entity {
 public:
    Entity(const char* filename, glm::vec3 location);
    ~Entity();
    Mesh* getMesh(void);
    glm::vec3 getLocation(void);

 private:
    glm::vec3 location;
    Mesh* mesh;
    
};
