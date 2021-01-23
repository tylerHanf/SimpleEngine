#include "ObjectHandles.h"
#include "Debug.h"

ObjectHandles::ObjectHandles(DataFileHandler* loadedData) {
  moveBaseIndex = loadedData->NumMeshes()-3;
  currentVBO = moveBaseIndex;
  for (int i=moveBaseIndex; i<moveBaseIndex+3; i++) {
    // fix get mesh index when other handles are made
    Debug::Instance().PrintError(moveBaseIndex);
    meshData* curMesh = loadedData->GetMesh(i);
    handleMeshes[i-moveBaseIndex] = Entity(i, glm::vec3(0.0f, 0.0f, 0.0f),
					curMesh->min, curMesh->max);
  }
}

// TODO: figure how to get size
float ObjectHandles::getSize() {
  Debug::Instance().PrintError(handleType);
  return 10*(handleMeshes[0].getCollider()->getSize().y / 2);
}

// TODO: figure how to get vbo index of current
int ObjectHandles::getVBOIdx() {
  return currentVBO;
}

int ObjectHandles::numTriangles() {
  return 0;
}

void ObjectHandles::switchMode(HandleType newMode) {
  handleType = newMode;
  currentVBO = moveBaseIndex+newMode;
}
