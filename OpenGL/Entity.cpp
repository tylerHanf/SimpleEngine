#include "Entity.h"
#include "Debug.h"

Entity::Entity(const char* filename, glm::vec3 locationObj, Entity_Type aObjType) :
    objType(aObjType)
{
    if (objType != Entity_Type(LIGHT))
        mesh = new Mesh(filename);
    else
	mesh = NULL;
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

const Entity_Type Entity::getEntityType(void) {
    return objType;
}

//Bad implementation if entity has multiple meshes
const void* Entity::getMeshVertices(void) {
    return (const void*) mesh->getVertices();
}

int Entity::numMeshVertices(void) {
    return mesh->getNumVertices();
}
 
