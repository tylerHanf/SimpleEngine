#pragma once

#include "Mesh.h"
#include "Collider.h"
#include <GLM/glm.hpp>

class Entity {
 public:
  Entity(const char* filename, glm::vec3 location);
  Entity(const char* filename, glm::vec3 location, bool colType);
  ~Entity();
  Mesh* getMesh(void);
  glm::vec3 getLocation(void);
  const void* getMeshVertices(void);
  int numMeshVertices(void);
  glm::vec3 getMax(void);
  glm::vec3 getMin(void);
  glm::mat4 getTransform(void);
  bool intersects(glm::vec3 rayOrigin, glm::vec3 rayDir, float* intersection);
  bool canCollide(void);
  void addCollider(void);
  bool isBoxCol(void);
  bool showingCollider(void);
  void toggleCollider(void);
  Collider* getCollider(void);  
    
 private:
  glm::vec3 location;
  glm::mat4 transform;  
  //Assume entity only has one mesh, could
  //make vector if there is a potential for multiple
  Mesh* mesh;
  bool hasCollider;
  Collider collider;
};
