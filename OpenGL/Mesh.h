#pragma once
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
    
 private:
    std::vector<float> Vertices;
};
