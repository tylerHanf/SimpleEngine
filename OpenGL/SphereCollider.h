#pragma once

#include <GLM/glm.hpp>
#include <GLM/vec3.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "Debug.h"

class SphereCollider {
 public:
  SphereCollider() = default;
  SphereCollider(glm::vec3 side, glm::vec3 incenter);
  glm::vec3 getCenter(void);
  float getRadius(void);
  bool intersects(glm::vec3 p, glm::vec3 d);

 private:
  glm::vec3 center;
  float radius;
};
