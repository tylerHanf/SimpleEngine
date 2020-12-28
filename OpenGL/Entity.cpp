#include "Entity.h"
#include "Debug.h"
#include <math.h>

Entity::Entity(int inMeshIdx, glm::vec3 locationObj) {
  location = locationObj;
  transform = glm::translate(glm::mat4(1.0f), location);
  meshIdx = inMeshIdx;
  hasCollider = false;
}

glm::vec3 Entity::getLocation(void) {
    return location;
}

glm::mat4 Entity::getTransform(void) {
  return transform;
}

int Entity::getMeshIdx(void) {
  return meshIdx;
}

bool Entity::canCollide(void) {
  return hasCollider;
}

bool Entity::isBoxCol(void) {
  return collider.isBoxCol();
}

bool Entity::showingCollider(void) {
  return collider.isShowing();
}

void Entity::toggleCollider(void) {
  return collider.toggleShow();
}

Collider* Entity::getCollider(void) {
  return &collider;
}

void Entity::addCollider(void) {
  hasCollider = true;
}

 
 

