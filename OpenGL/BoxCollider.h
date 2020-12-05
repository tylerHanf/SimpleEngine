#pragma once

#include <GLM/vec3.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "Debug.h"

class BoxCollider {
 public:
  BoxCollider(void);
  BoxCollider(glm::vec3 min, glm::vec3 max);
  glm::mat4 getTransform(void);
  glm::vec3 getCenter(void);
  glm::vec3 getHalfLengths(void);
  void RenderCollider(void);
  bool isPicked(glm::vec3 ray);

 /*

   mat4 points:
   [center, 0.0],
   [xNorm, 0.0],
   [yNorm, 0.0],
   [zNorm, 0.0]
 */
  
 private:
  glm::vec3 size;
  glm::vec3 halfLengths;
  glm::vec3 center;
  glm::mat4 points;
  glm::mat4 transform;
};
