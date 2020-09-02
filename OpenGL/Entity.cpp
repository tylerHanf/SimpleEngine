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
