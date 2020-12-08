#pragma once

#include <GLM/vec3.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "Debug.h"

class Collider {
 public:
  Collider(void);
  Collider(glm::vec3* min, glm::vec3* max, glm::vec3* location, bool colType);
  glm::mat4 getTransform(void);
  glm::vec3 getCenter(void);
  bool isBoxCol(void);
  bool isShowing(void);
  bool intersects(glm::vec3 origin, glm::vec3 direction, float* intersection);
  int getEntityID(void);
  void toggleShow();
  void toggleShape(void);

 private:
  bool show = false;
  bool isBox = true;
  int entID = 1;
  glm::vec3 size;
  glm::vec3* location;
  glm::vec3* min;
  glm::vec3* max;

  bool boxIntersects(glm::vec3 origin, glm::vec3 direction, float* intersection);
  bool sphereIntersects(glm::vec3 origin, glm::vec3 direction, float* intersection);    
};
