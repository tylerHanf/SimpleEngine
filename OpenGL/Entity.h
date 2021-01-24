#pragma once

#include "Collider.h"
#include <GLM/glm.hpp>

class Entity {
 public:
  Entity(void);
  Entity(int inMeshIdx, glm::vec3 location, glm::vec3 inMin, glm::vec3 inMax);

  int getMeshIdx(void);

  bool intersects(glm::vec3 rayOrigin, glm::vec3 rayDir, float* intersection);
  bool canCollide(void);
  void addCollider(void);
  bool isBoxCol(void);
  bool showingCollider(void);
  void toggleCollider(void);
  Collider* getCollider(void);
  
  glm::vec3 getLocation(void);
  glm::mat4 getTransform(void);
  glm::mat4 getTranslate(void);
  glm::mat4 getScale(void);
  glm::mat4 getRotate(void);
  glm::vec3 getScaledSize(void);
  
  void setLocation(glm::vec3 newLocation);
  void setTranslate(glm::vec3 translateVals);
  void setScale(glm::vec3 scaleVals);
  void setRotate(glm::mat4 model, float angle, glm::vec3 rotationAxis);
    
 private:
  //struct Rotate;
  glm::vec3 location;
  glm::mat4 translate;
  glm::mat4 scale;
  glm::mat4 rotate;
  //Assume entity only has one mesh, could
  //make vector if there is a potential for multiple
  int meshIdx;
  //int textureID;       // MAYBE
  bool hasCollider;
  Collider collider;
};
