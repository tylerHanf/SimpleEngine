#pragma once

#include <GLM/vec3.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "EntityHandler.h"
#include "Debug.h"

class MouseRay {
 public:
  MouseRay(void);
  void Update(double xPos, double yPos, int width, int height,
	      glm::mat4 pMat, glm::mat4 vMat, glm::vec3 orig);
  glm::vec3 getDirection(void);
  glm::vec3 getOrigin(void);
  int pointingAt(EntityHandler* entities);
  
 private:
  glm::vec3 ray;
  glm::vec3 origin;
};
