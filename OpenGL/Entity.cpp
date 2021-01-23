#include "Entity.h"
#include "Debug.h"
#include <math.h>

Entity::Entity(void) :
  collider(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), BOX)
{
  location = glm::vec3(0.0f, 0.0f, 0.0f);
  transform = glm::mat4(1.0f);
  meshIdx = 0;
  hasCollider = false;
}

Entity::Entity(int inMeshIdx, glm::vec3 locationObj, glm::vec3 inMin, glm::vec3 inMax) :
  collider(inMin, inMax, locationObj, BOX)  

{
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

 
 

