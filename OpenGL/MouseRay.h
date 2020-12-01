#pragma once

#include <GLM/vec3.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "Entity.h"
#include "Debug.h"

class MouseRay {
 public:
  MouseRay(void);
  void Update(float xPos, float yPos, int width, int height,
	      glm::mat4 pMat, glm::mat4 vMat);
  glm::vec3 getRay(void);
  Entity* pointingAt(void);
  
 private:
  glm::vec3 ray;
  int max_dist = 200;
};
