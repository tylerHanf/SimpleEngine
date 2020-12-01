#include "MouseRay.h"

MouseRay::MouseRay(void) {
  ray = glm::vec3(1.0f, 1.0f, 1.0f);
}

void MouseRay::Update(float xPos, float yPos, int width, int height,
		      glm::mat4 pMat, glm::mat4 vMat) {
  
  float x = (2.0f * xPos) / width - 1.0f;
  float y = 1.0f - (2.0f * yPos) / height;
  
  glm::vec4 rayClip = glm::vec4(x, y, -1.0f, 1.0f);
  glm::vec4 ray_eye = glm::inverse(pMat) * rayClip;
  ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);

  glm::vec4 temp = glm::inverse(vMat) * ray_eye;
  glm::vec3 ray_wor = glm::vec3(temp.x, temp.y, temp.z);
  ray = glm::normalize(ray_wor);
  Debug::Instance().PrintError(ray.x);
}

glm::vec3 MouseRay::getRay(void) {
  return ray;
}

Entity* MouseRay::pointingAt(void) {
  return NULL;
}
