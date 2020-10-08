#pragma once

#include "Mesh.h"
#include <GLM/glm.hpp>

class Entity {
 public:
    Entity(const char* filename, glm::vec3 location);
    ~Entity();
    Mesh* getMesh(void);
    glm::vec3 getLocation(void);
    const void* getMeshVertices(void);
    int numMeshVertices(void);

 private:
    glm::vec3 location;
    //Assume entity only has one mesh, could
    //make vector if there is a potential for multiple
    Mesh* mesh;
};
