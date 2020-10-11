#include "EntityHandler.h"

#include "Debug.h"

void EntityHandler::AddEntity(const char* objPath, glm::vec3 pos) {
    Entity* newEntity = new Entity(objPath, pos);
    entities.push_back(newEntity);
}

Entity* EntityHandler::GetEntity(unsigned int idx) {
    if (!(idx >= entities.size()))
	return entities[idx];
    
    Debug::Instance().PrintError("Failed to get entity: index out of range");
    return NULL;
}

int EntityHandler::NumEntities() {
    return entities.size();
}
