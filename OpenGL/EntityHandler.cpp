#include "EntityHandler.h"
#include "Debug.h"

EntityHandler::EntityHandler(DataFileHandler* loadedData) {
  meshData = loadedData->GetObjectData();
}

void EntityHandler::AddEntity(int meshID, glm::vec3 pos) {
    Entity* newEntity = new Entity(meshID, pos, true);
    entities.push_back(newEntity);
}

Entity* EntityHandler::GetEntity(unsigned int idx) {
    if (!(idx >= entities.size()))
	return entities[idx];
    
    Debug::Instance().PrintError("Failed to get entity: index out of range");
    return NULL;
}

int EntityHandler::NumEntities() {
    return meshData.size();
}

int EntityHandler::NumMeshes() {
  return meshData.size();
}

int EntityHandler::NumTriangles(int meshIdx) {
  return meshData[meshIdx].vertData.size() / 6;
}

std::vector<float> EntityHandler::GetMesh(int meshIdx) {
  return meshData[meshIdx].vertData;
}

const char* EntityHandler::GetMeshName(int meshIdx) {
  return meshData[meshIdx].meshName.c_str();
}

unsigned char* EntityHandler::GetTexture(int meshIdx, int* width, int* height) {
  *width = meshData[meshIdx].textWidth;
  *height = meshData[meshIdx].textHeight;
  return meshData[meshIdx].textData;
}
