#include "BoxCollider.h"

BoxCollider::BoxCollider(void) {
  size = glm::vec3(1.0f);
  halfLengths = glm::vec3(1.0f);
  points = glm::mat4(1.0f);
  transform = glm::mat4(1.0f);
}

BoxCollider::BoxCollider(glm::vec3 min, glm::vec3 max) {
  size = glm::vec3((max.x-min.x)/2, (max.y-min.y)/2, (max.z-min.z)/2);
  halfLengths = glm::vec3(size.x / 2, size.y / 2, size.z / 2);
  mins = min;
  maxs = max;
  points = glm::mat4(1.0f);
  points[0] = glm::vec4((min.x+max.x)/2, (min.y+max.y)/2, (min.z+max.z)/2, 1.0f);  
  transform = glm::translate(glm::mat4(1), glm::vec3(points[0].x, points[0].y, points[0].z)) *
    glm::scale(glm::mat4(1), size);
}

glm::mat4 BoxCollider::getTransform(void) {
  return transform;
}

glm::vec3 BoxCollider::getCenter(void) {
  return glm::vec3(points[0].x, points[0].y, points[0].z);
}

glm::vec3 BoxCollider::getHalfLengths(void) {
  return halfLengths;
}

bool BoxCollider::intersects(glm::vec3 origin, glm::vec3 direction) {
  float tmin = 0.0f;
  float tmax = 100000.0f;
  float f, e;
  glm::vec3 center = glm::vec3(0.0, 0.0, -10.0);
  glm::vec3 p = center - origin;
  glm::vec3 xaxis(1.0f, 0.0f, 0.0f);
  glm::vec3 yaxis(0.0f, 1.0f, 0.0f);
  glm::vec3 zaxis(0.0f, 0.0f, 1.0f);

  e = glm::dot(xaxis, p);
  f = glm::dot(direction, xaxis);

  if (fabs(f) > 0.001f) {
    float t1 = (e + mins.x) / f;
    float t2 = (e + maxs.x) / f;

    if (t1 > t2) {
      float temp = t1; t1 = t2; t2 = temp;
    }

    if (t2 < tmax) tmax = t2;
    if (t1 > tmin) tmin = t1;
    if (tmax < tmin) return false;
  }
  else if (-e + mins.x > 0.0f || -e + maxs.x < 0.0f) return false;

  e = glm::dot(yaxis, p);
  f = glm::dot(direction, yaxis);

  if (fabs(f) > 0.001f) {
    float t1 = (e + mins.y) / f;
    float t2 = (e + maxs.y) / f;

    if (t1 > t2) {
      float temp = t1; t1 = t2; t2 = temp;
    }

    if (t2 < tmax) tmax = t2;
    if (t1 > tmin) tmin = t1;
    if (tmax < tmin) return false;
  }
  else if (-e + mins.y > 0.0f || -e + maxs.y < 0.0f) return false;

  e = glm::dot(zaxis, p);
  f = glm::dot(direction, zaxis);

  if (fabs(f) > 0.001f) {
    float t1 = (e + mins.z) / f;
    float t2 = (e + maxs.z) / f;

    if (t1 > t2) {
      float temp = t1; t1 = t2; t2 = temp;
    }

    if (t2 < tmax) tmax = t2;
    if (t1 > tmin) tmin = t1;
    if (tmax < tmin) return false;
  }
  else if (-e + mins.z > 0.0f || -e + maxs.z < 0.0f) return false;  
  
  return true;
}
