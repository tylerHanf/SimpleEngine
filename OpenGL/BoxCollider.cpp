#include "BoxCollider.h"

BoxCollider::BoxCollider(void) {
  size = glm::vec3(1.0f);
  center = glm::vec3(1.0f);
  transform = glm::mat4(1.0f);
}

BoxCollider::BoxCollider(glm::vec3 min, glm::vec3 max) {
  size = glm::vec3((max.x-min.x)/2, (max.y-min.y)/2, (max.z-min.z)/2);
  center = glm::vec3((min.x+max.x)/2, (min.y+max.y)/2, (min.z+max.z)/2);
  transform = glm::translate(glm::mat4(1), center) * glm::scale(glm::mat4(1), size);
}

glm::mat4 BoxCollider::getTransform(void) {
  return transform;
}

bool BoxCollider::isPicked(glm::vec3 ray) {
  return false;
}
