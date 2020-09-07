#include "Entity.h"
#include "Debug.h"

Entity::Entity(const char* filename, glm::vec3 locationObj) {
    mesh = new Mesh(filename);
    location = locationObj;
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

//Bad implementation if entity has multiple meshes
const void* Entity::getMeshVertices(void) {
    return (const void*) mesh->getVertices();
}

int Entity::numMeshVertices(void) {
    return mesh->getNumVertices();
}

