#include "SphereCollider.h"
#include <math.h>

SphereCollider::SphereCollider(glm::vec3 side, glm::vec3 incenter) {
  center = incenter;
  //radius = fabs(side.x-center.x);
  radius = 0.5f;
}

glm::vec3 SphereCollider::getCenter(void) {
  return center;
}

float SphereCollider::getRadius(void) {
  return radius;
}

bool SphereCollider::intersects(glm::vec3 rayOrigin, glm::vec3 rayDir) {
  Debug::Instance().PrintError("Test collision");
  glm::vec3 l = center - rayOrigin;
  float s = glm::dot(l, rayDir);
  float l_square = glm::dot(l, l);

  if (s < 0 && l_square > radius*radius) return false;
  float m_square = l_square - s*s;
  if (m_square > radius) return false;
  Debug::Instance().PrintError("picked");
  return true;
}
