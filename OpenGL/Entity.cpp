#include "Entity.h"
#include "Debug.h"
#include <math.h>

Entity::Entity(const char* filename, glm::vec3 locationObj) {
     mesh = new Mesh(filename);
     location = locationObj;
     transform = glm::translate(glm::mat4(1.0f), location);
     hasCollider = false;
}

Entity::Entity(const char* filename, glm::vec3 locationObj, bool colType) {
     mesh = new Mesh(filename);
     location = locationObj;
     transform = glm::translate(glm::mat4(1.0f), location);
     collider = Collider(mesh->getMin(), mesh->getMax(), &location, colType);
     hasCollider = true;
}

Entity::~Entity(void) {
    delete mesh;
}

Mesh* Entity::getMesh(void) {
    return mesh;
}

glm::vec3 Entity::getLocation(void) {
    return location;
}

glm::vec3 Entity::getMax(void) {
  return *(mesh->getMax());
}

glm::vec3 Entity::getMin(void) {
  return *(mesh->getMin());
}

// Bad implementation if entity has multiple meshes
const void* Entity::getMeshVertices(void) {
    return (const void*) mesh->getVertices();
}

int Entity::numMeshVertices(void) {
    return mesh->getNumVertices();
}

glm::mat4 Entity::getTransform(void) {
  return transform;
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

 
 

