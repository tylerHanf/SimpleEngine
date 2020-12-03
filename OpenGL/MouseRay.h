#pragma once

#include <GLM/vec3.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "EntityHandler.h"
#include "Debug.h"

class MouseRay {
 public:
  MouseRay(void);
  void Update(float xPos, float yPos, int width, int height,
	      glm::mat4 pMat, glm::mat4 vMat);
  glm::vec3 getOrigin(void);
  glm::vec3 getDirection(void);
  Entity* pointingAt(EntityHandler* entities);
  
 private:
  glm::vec3 outOrigin;
  glm::vec3 outDir;
  int max_dist = 200;
};
