#include "Entity.h"
#include "Debug.h"
#include <math.h>

Entity::Entity(void) :
  collider(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), BOX)
{
  location = glm::vec3(0.0f, 0.0f, 0.0f);
  translate = glm::translate(glm::mat4(1.0f), location);
  scale = glm::mat4(1.0f);
  rotate = glm::mat4(1.0f);
  meshIdx = 0;
  hasCollider = false;
}

Entity::Entity(int inMeshIdx, glm::vec3 locationObj, glm::vec3 inMin, glm::vec3 inMax) :
  collider(inMin, inMax, locationObj, BOX)  
{
  location = locationObj;
  translate = glm::translate(glm::mat4(1.0f), location);
  scale = glm::mat4(1.0f);
  rotate = glm::mat4(1.0f);
  meshIdx = inMeshIdx;
  hasCollider = false;
  Debug::Instance().PrintError("Collider size");
  Debug::Instance().PrintError(collider.getSize().x); 
}

glm::vec3 Entity::getLocation(void) {
    return location;
}

glm::mat4 Entity::getTransform(void) {
  return translate*scale*rotate;
}

glm::mat4 Entity::getTranslate(void) {
  return translate;
}

glm::mat4 Entity::getScale(void) {
  return scale;
}

glm::mat4 Entity::getRotate(void) {
  return rotate;
}

glm::vec3 Entity::getScaledSize(void) {
  glm::vec3 size = collider.getSize();
  return glm::vec3(scale[0][0]*size.x, scale[1][1]*size.y, scale[2][2]*size.z);
}

void Entity::setLocation(glm::vec3 newLocation) {
  location = newLocation;
}

void Entity::setTranslate(glm::vec3 translateVals) {
  translate = glm::translate(glm::mat4(1.0f), translateVals);
}

void Entity::setScale(glm::vec3 scaleVals) {
  scale = glm::scale(glm::mat4(1.0f), scaleVals);
}

void Entity::setRotate(glm::mat4 model, float angle, glm::vec3 rotationAxis) {
  rotate = glm::rotate(glm::mat4(1.0f), angle, rotationAxis);
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

 
 

