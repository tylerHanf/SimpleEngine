#include "Collider.h"
#include "Debug.h"

Collider::Collider(void) {
  size = glm::vec3(1.0f);
  //location = &glm::vec3(1.0f);
  min = NULL;
  max = NULL;
}

Collider::Collider(glm::vec3* inMin, glm::vec3* inMax, glm::vec3* inLocation, bool colType) {

  min = inMin;
  max = inMax;
  location = inLocation;
  size = glm::vec3(((*max).x-(*min).x)/2, ((*max).y-(*min).y)/2, ((*max).z-(*min).z)/2);
  Debug::Instance().PrintError((*max).x);  
  isBox = colType;
  entID = colType == true ? 1 : 2;
}

glm::mat4 Collider::getTransform(void) {
  return glm::translate(glm::mat4(1.0), *location) * glm::scale(glm::mat4(1.0), size);
}

glm::vec3 Collider::getCenter(void) {
  return *location;
}

bool Collider::isBoxCol(void) {
  return isBox;
}

bool Collider::isShowing(void) {
  return show;
}

void Collider::toggleShow(void) {
  show = !show;
}

void Collider::toggleShape(void) {
  if (isBox) entID = 2;
  else entID = 1;
  isBox = !isBox;
}

int Collider::getEntityID(void) {
  return entID;
}

bool Collider::sphereIntersects(glm::vec3 rayOrigin, glm::vec3 rayDir, float* intersection) {
  float radius = fabs((*location).x - (*max).x);
  glm::vec3 l = *location - rayOrigin;
  float s = glm::dot(l, rayDir);
  float l_square = glm::dot(l, l);
  float r_square = radius * radius;
  if (s < 0 && l_square > r_square) return false;
  float m_square = l_square - s*s;
  if (m_square > radius) return false;
  float q = sqrt(r_square - m_square);
  if (l_square > r_square) *intersection = s - q;
  else *intersection = s + q;
  return true;    
}

bool Collider::boxIntersects(glm::vec3 rayOrigin, glm::vec3 rayDir, float* intersection) {
  float tmin = 0.0f;
  float tmax = 100000.0f;
  float f, e, t1, t2, temp;
  glm::vec3 p = *location - rayOrigin;

  /*
    TODO: find the axis normals
   */
  
  glm::vec3 xaxis(1.0f, 0.0f, 0.0f);
  glm::vec3 yaxis(0.0f, 1.0f, 0.0f);
  glm::vec3 zaxis(0.0f, 0.0f, 1.0f);
  
  // check along x-axis
  e = glm::dot(xaxis, p);
  f = glm::dot(rayDir, xaxis);
  if (fabs(f) > 0.001f) {
    t1 = (e + (*min).x) / f;
    t2 = (e + (*max).x) / f;
    if (t1 > t2) {
      temp = t1; t1 = t2; t2 = temp;
    }
    if (t2 < tmax) tmax = t2;
    if (t1 > tmin) tmin = t1;
    if (tmax < tmin) return false;
  }
  else if (-e + (*min).x > 0.0f || -e + (*max).x < 0.0f) return false;

  // check along y-axis
  e = glm::dot(yaxis, p);
  f = glm::dot(rayDir, yaxis);
  if (fabs(f) > 0.001f) {
    t1 = (e + (*min).y) / f;
    t2 = (e + (*max).y) / f;
    if (t1 > t2) {
      temp = t1; t1 = t2; t2 = temp;
    }
    if (t2 < tmax) tmax = t2;
    if (t1 > tmin) tmin = t1;
    if (tmax < tmin) return false;
  }
  else if (-e + (*min).y > 0.0f || -e + (*max).y < 0.0f) return false;

  // check along z-axis
  e = glm::dot(zaxis, p);
  f = glm::dot(rayDir, zaxis);
  if (fabs(f) > 0.001f) {
    t1 = (e + (*min).z) / f;
    t2 = (e + (*max).z) / f;
    if (t1 > t2) {
      temp = t1; t1 = t2; t2 = temp;
    }
    if (t2 < tmax) tmax = t2;
    if (t1 > tmin) tmin = t1;
    if (tmax < tmin) return false;
  }
  else if (-e + (*min).z > 0.0f || -e + (*max).z < 0.0f) return false;
  if (tmin > 0) {
    *intersection = tmin;
    return true;
  }
  *intersection = tmax;
  return true;
}

bool Collider::intersects(glm::vec3 rayOrigin, glm::vec3 rayDir, float* intersection) {
  if (isBox) {
    return boxIntersects(rayOrigin, rayDir, intersection);
  }
  return sphereIntersects(rayOrigin, rayDir, intersection);
}

