#pragma once

#include <GLM/vec3.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "Debug.h"

class BoxCollider {
 public:
  BoxCollider(void);
  BoxCollider(glm::vec3 min, glm::vec3 max);
  glm::mat4 getTransform(void);
  void RenderCollider(void);
  bool isPicked(glm::vec3 ray);
  
 private:
  glm::vec3 size;
  glm::vec3 center;
  glm::mat4 transform;
};
