#include "Entity.h"

Entity::Entity(const char* filename, glm::vec3 location) {
    mesh = new Mesh(filename);
    this->location = location;
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

//Bad implementation if entity has multiple meshes
std::vector<float> Entity::getMeshNormals(void) {
    return mesh->getNormals();
}

int Entity::numMeshVertices(void) {
    return mesh->getNumVertices();
}

