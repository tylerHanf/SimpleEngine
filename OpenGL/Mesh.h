#pragma once
#include "Debug.h"
#include <vector>
#include <string>
#include <GLM/vec3.hpp>

/*
  Contains Data for a single Mesh
  The mesh is loaded via Assimp

  TODO: handle textures...same class?
 */
class Mesh {
 public:
    Mesh(const std::string& fileName);
    const float* getVertices(void);
    int getNumVertices(void);
    glm::vec3 getMax(void);
    glm::vec3 getMin(void);
    
 private:
    std::vector<float> Vertices;
    glm::vec3 min = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 max = glm::vec3(0.0f, 0.0f, 0.0f);
    float size = 0;
};
