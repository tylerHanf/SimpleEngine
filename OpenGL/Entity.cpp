#include "Entity.h"
#include "Debug.h"

Entity::Entity(const char* filename, glm::vec3 locationObj) {
     mesh = new Mesh(filename);
     location = locationObj;
     bcollider = BoxCollider(mesh->getMin(), mesh->getMax());
     collider = SphereCollider(mesh->getMax(), location);
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
  return mesh->getMax();
}

glm::vec3 Entity::getMin(void) {
  return mesh->getMin();
}

BoxCollider* Entity::getBoxCollider(void) {
  return &bcollider;
}

SphereCollider* Entity::getSphereCollider(void) {
  return &collider;
}

//Bad implementation if entity has multiple meshes
const void* Entity::getMeshVertices(void) {
    return (const void*) mesh->getVertices();
}

int Entity::numMeshVertices(void) {
    return mesh->getNumVertices();
}
 
