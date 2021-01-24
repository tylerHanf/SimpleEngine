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

float ObjectHandles::getSize() {
  return 10*(handleMeshes[0].getCollider()->getSize().y / 2);
}

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

void ObjectHandles::updateLocation(glm::vec3 location) {
  for (int i=0; i<3; i++) {
    handleMeshes[i].setLocation(location);
  }
}

void ObjectHandles::bindObject(Entity* selectedEntity) {
  // assume size is updated from scale factor
  /*
  for (int i=0; i<3; i++) {
    handleMeshes[i].setLocation(selectedEntity->getLocation());
    }*/

  glm::mat4 translateMat = selectedEntity->getTranslate();
  glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 10.0f));
  transforms[0] = translateMat;
  transforms[0] *= scaleMat;

  transforms[1] = translateMat;
  transforms[1] *= glm::rotate(glm::mat4(1.0f), 3.14f/2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
  transforms[1] *= scaleMat;

  transforms[2] = translateMat;
  transforms[2] *= glm::rotate(glm::mat4(1.0f), 3.14f/2.0f, glm::vec3(0.0f, 0.0f, 1.0f));
  transforms[2] *= scaleMat;
}

glm::vec3 ObjectHandles::getLocation(void) {
  return handleMeshes[handleType].getLocation();
}

int ObjectHandles::handleSelected(glm::vec3 origin, glm::vec3 ray) {
  int pickedEnt = -1;
  float current = 0;
  float closest = 10000;
  
  for (int i=0; i<3; i++) {
    Collider* curCollider = handleMeshes[i].getCollider();
    if (curCollider->intersects(origin, ray, &current)) {
      if (current < closest) {
	closest = current;
	pickedEnt = i;
      }
    }
  }
  return pickedEnt;
}

glm::mat4 ObjectHandles::getTransform(int transformIdx) {
  return transforms[transformIdx];
}
