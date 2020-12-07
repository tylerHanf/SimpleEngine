#include "Entity.h"
#include "Debug.h"
#include <math.h>

Entity::Entity(const char* filename, glm::vec3 locationObj) {
     mesh = new Mesh(filename);
     location = locationObj;
     transform = glm::translate(glm::mat4(1.0f), location);
     hasCollider = false;
     isBox = false;
     showCol = false;
}

Entity::Entity(const char* filename, glm::vec3 locationObj, bool colType) {
     mesh = new Mesh(filename);
     location = locationObj;
     transform = glm::translate(glm::mat4(1.0f), location);
     hasCollider = true;
     isBox = colType;
     showCol = false;
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

glm::vec3 Entity::getMax(void) {
  return mesh->getMax();
}

glm::vec3 Entity::getMin(void) {
  return mesh->getMin();
}

// Bad implementation if entity has multiple meshes
const void* Entity::getMeshVertices(void) {
    return (const void*) mesh->getVertices();
}

int Entity::numMeshVertices(void) {
    return mesh->getNumVertices();
}

glm::mat4 Entity::getTransform(void) {
  return transform;
}

bool Entity::canCollide(void) {
  return hasCollider;
}

bool Entity::isBoxCol(void) {
  return isBox;
}

bool Entity::showingCollider(void) {
  return showCol;
}

void Entity::toggleCollider(void) {
  showCol = !showCol;
}

/*
  Determine if object is intersected 
  given ray using sphere collider
 */
bool Entity::sphereIntersect(glm::vec3 rayOrigin, glm::vec3 rayDir, float* intersection) {
  float radius = fabs(location.x - mesh->getMax().x);
  glm::vec3 l = location - rayOrigin;
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

/*
  Determine if object is intersected 
  given ray using box collider
 */
bool Entity::boxIntersect(glm::vec3 rayOrigin, glm::vec3 rayDir, float* intersection) {
  glm::vec3 min = mesh->getMin();
  glm::vec3 max = mesh->getMax();
  float tmin = 0.0f;
  float tmax = 100000.0f;
  float f, e, t1, t2, temp;
  glm::vec3 center = glm::vec3((min.x+max.x/2)/2, (min.y+max.y)/2, (min.z+max.z)/2);
  glm::vec3 p = location - rayOrigin;

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
    t1 = (e + min.x) / f;
    t2 = (e + max.x) / f;
    if (t1 > t2) {
      temp = t1; t1 = t2; t2 = temp;
    }
    if (t2 < tmax) tmax = t2;
    if (t1 > tmin) tmin = t1;
    if (tmax < tmin) return false;
  }
  else if (-e + min.x > 0.0f || -e + max.x < 0.0f) return false;

  // check along y-axis
  e = glm::dot(yaxis, p);
  f = glm::dot(rayDir, yaxis);
  if (fabs(f) > 0.001f) {
    t1 = (e + min.y) / f;
    t2 = (e + max.y) / f;
    if (t1 > t2) {
      temp = t1; t1 = t2; t2 = temp;
    }
    if (t2 < tmax) tmax = t2;
    if (t1 > tmin) tmin = t1;
    if (tmax < tmin) return false;
  }
  else if (-e + min.y > 0.0f || -e + max.y < 0.0f) return false;

  // check along z-axis
  e = glm::dot(zaxis, p);
  f = glm::dot(rayDir, zaxis);
  if (fabs(f) > 0.001f) {
    t1 = (e + min.z) / f;
    t2 = (e + max.z) / f;
    if (t1 > t2) {
      temp = t1; t1 = t2; t2 = temp;
    }
    if (t2 < tmax) tmax = t2;
    if (t1 > tmin) tmin = t1;
    if (tmax < tmin) return false;
  }
  else if (-e + min.z > 0.0f || -e + max.z < 0.0f) return false;
  if (tmin > 0) {
    *intersection = tmin;
    return true;
  }
  *intersection = tmax;
  return true;
}  
 
bool Entity::intersects(glm::vec3 rayOrigin, glm::vec3 rayDir, float* intersection) {
  if (isBox) {
    return boxIntersect(rayOrigin, rayDir, intersection);
  }
  return sphereIntersect(rayOrigin, rayDir, intersection);
}
