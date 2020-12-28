#pragma once

#include "Collider.h"
#include <GLM/glm.hpp>

class Entity {
 public:
  Entity(int inMeshIdx, glm::vec3 location, glm::vec3 inMin, glm::vec3 inMax);
  glm::vec3 getLocation(void);
  int getMeshIdx(void);
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
  int meshIdx;
  //int textureID;       // MAYBE
  bool hasCollider;
  Collider collider;
};
