#include "MouseRay.h"

MouseRay::MouseRay(void) {
  outOrigin = glm::vec3(1.0f);
  outDir = glm::vec3(1.0f);
}

void MouseRay::Update(float xPos, float yPos, int width, int height,
		      glm::mat4 pMat, glm::mat4 vMat) {

  glm::vec4 rayStart(((float)xPos/(float)width - 0.5f) * 2.0f,
		     ((float)yPos/(float)height - 0.5f) * 2.0f,
		     -1.0f,
		     1.0f);
  glm::vec4 rayEnd(((float)xPos/(float)width - 0.5) * 2.0f,
		   ((float)yPos/(float)height - 0.5) * 2.0f,
		   0.0f,
		   1.0f);
  
  glm::mat4 projInverse = glm::inverse(pMat);
  glm::mat4 viewInverse = glm::inverse(vMat);

  //float x = (2.0f * xPos) / width - 1.0f;
  //Debug::Instance().PrintError(x);
  //float y = 1.0f - (2.0f * yPos) / height;
  //Debug::Instance().PrintError(y);
  
  //glm::vec4 rayClip = glm::vec4(x, y, -1.0f, 1.0f);
  //glm::vec4 ray_eye = glm::inverse(pMat) * rayClip;
  //ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);

  //glm::vec4 temp = glm::inverse(vMat) * ray_eye;
  //glm::vec3 ray_wor = glm::vec3(temp.x, temp.y, temp.z);
  //ray = glm::normalize(ray_wor);

  glm::vec4 rayStart_cam = projInverse * rayStart; rayStart_cam /= rayStart_cam.w;
  glm::vec4 rayEnd_cam = projInverse * rayEnd; rayEnd_cam /= rayEnd_cam.w;
  glm::vec4 rayStart_world = viewInverse * rayStart_cam; rayStart_world /= rayStart_world.w;
  glm::vec4 rayEnd_world = viewInverse * rayEnd_cam; rayEnd_world /= rayEnd_world.w;

  glm::vec3 rayDir_world(rayEnd_world - rayStart_world);
  rayDir_world = glm::normalize(rayDir_world);

  outOrigin = glm::vec3(rayStart_world);
  outDir = glm::normalize(rayDir_world);
}

glm::vec3 MouseRay::getOrigin(void) {
  return outOrigin;
}

glm::vec3 MouseRay::getDirection(void) {
  return outDir;
}

Entity* MouseRay::pointingAt(EntityHandler* entities) {
  // TODO: See if I can only account for entities in view
  float tmin, tmax;
  glm::vec3 p;
  BoxCollider* curCollider = NULL;
  for (int i=0; i<entities->NumEntities(); i++) {
    curCollider = entities->GetEntity((unsigned int) i)->getBoxCollider();
    tmin = -10000000;
    tmax = 10000000;

    //p = curCollider->getCenter() - ray;
    
  }
  
  return NULL;
}
