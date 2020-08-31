#pragma once
#include <vector>
#include <string>
#include <GLM/vec3.hpp>

/*
  Contains Data for a single Mesh
  The mesh is loaded via Assimp
 */
class Mesh {
 public:
    Mesh(const std::string& fileName);
    std::vector<float>& getVertices();
    std::vector<float>& getNormals();
    
 private:
    std::vector<float> Vertices;
    std::vector<float> Normals;
};
