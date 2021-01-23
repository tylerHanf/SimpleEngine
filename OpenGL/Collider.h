#pragma once

#include <GLM/vec3.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "Debug.h"

enum ColType {
  SPHERE,
  BOX
};

class Collider {
 public:
  Collider(glm::vec3 min, glm::vec3 max, glm::vec3 location, ColType colType);
  glm::mat4 getTransform(void);
  glm::vec3 getCenter(void);
  bool isBoxCol(void);
  bool isShowing(void);
  bool intersects(glm::vec3 origin, glm::vec3 direction, float* intersection);
  void toggleShow();
  glm::vec3& getSize(void);

 private:
  bool show = false;
  ColType colliderType = BOX;
  glm::vec3 size;
  glm::vec3 location;
  glm::vec3 min;
  glm::vec3 max;

  bool boxIntersects(glm::vec3 origin, glm::vec3 direction, float* intersection);
  bool sphereIntersects(glm::vec3 origin, glm::vec3 direction, float* intersection);    
};
