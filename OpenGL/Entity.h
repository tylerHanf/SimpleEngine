#pragma once

#include "Mesh.h"
#include <GLM/glm.hpp>

enum Entity_Type {
     PLAYER,
     WORLD_OBJ,
     LIGHT
};

class Entity {
 public:
    Entity(const char* filename, glm::vec3 location, Entity_Type objType);
    ~Entity();
    Mesh* getMesh(void);
    glm::vec3 getLocation(void);
    const void* getMeshVertices(void);
    int numMeshVertices(void);
    const Entity_Type getEntityType(void);

 private:
    glm::vec3 location;
    //Assume entity only has one mesh, could
    //make vector if there is a potential for multiple
    Mesh* mesh;
    const Entity_Type objType;
};
