#include "MouseRay.h"

MouseRay::MouseRay(void) {
  origin = glm::vec3(1.0f);
  ray = glm::vec3(1.0f);
}

void MouseRay::Update(double xPos, double yPos, int width, int height,
		      glm::mat4 pMat, glm::mat4 vMat, glm::vec3 orig) {

  float normx = (2.0f * xPos) / width - 1.0f;
  float normy = 1.0f - (2.0f * yPos) / height;
  glm::vec4 clipSpace = glm::vec4(normx, normy, -1.0, 1.0);
  glm::vec4 eye = glm::inverse(pMat) * clipSpace;
  eye = glm::vec4(eye.x, eye.y, -1.0, 0.0);
  glm::vec4 worldSpace = glm::inverse(vMat) * eye;
  glm::vec3 space = glm::vec3(worldSpace.x, worldSpace.y, worldSpace.z);
  ray = glm::normalize(space);
  
  origin = orig;
}

glm::vec3 MouseRay::getDirection(void) {
  return ray;
}

glm::vec3 MouseRay::getOrigin(void) {
  return origin;
}

Entity* MouseRay::pointingAt(EntityHandler* entities) {
  Entity* entity = entities->GetEntity(1);
  SphereCollider* collider = entity->getSphereCollider();
  
  if (collider->intersects(origin, ray)) return entity;
  return NULL;
}
