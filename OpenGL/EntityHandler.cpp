#include "EntityHandler.h"
#include "Debug.h"

EntityHandler::EntityHandler(DataFileHandler* loadedData) {
  //meshData = loadedData->GetObjectData();
}

void EntityHandler::AddEntity(int meshID, glm::vec3 pos, glm::vec3 inMin, glm::vec3 inMax) {
  Entity newEntity = Entity(meshID, pos, inMin, inMax);
  Debug::Instance().PrintError(meshID);
  entities.push_back(newEntity);
}

void EntityHandler::RemoveEntity(int meshID) {
  if (meshID > -1 && meshID < entities.size())
    entities.erase(entities.begin() + meshID);
  else
    Debug::Instance().PrintError("Remove entity out of range");
}

Entity* EntityHandler::GetEntity(unsigned int idx) {
    if (!(idx >= entities.size() || idx < 0))
      return &(entities[idx]);
    
    Debug::Instance().PrintError("Failed to get entity: index out of range");
    return NULL;
}

int EntityHandler::NumEntities() {
    return entities.size();
}

