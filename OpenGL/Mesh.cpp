#include "Mesh.h"
#include "Debug.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/*
Contains Mesh data (currently just vertices and normals)
*/
Mesh::Mesh(const std::string& filename) {


	// Get min
	if (xVert < min.x)
	  min.x = xVert;
	if (yVert < min.y)
	  min.y = yVert;
	if (zVert < min.z)
	  min.z = zVert;
	
	// Get max 
	if (xVert > max.x)
	  max.x = xVert;
	if (yVert > max.y)
	  max.y = yVert;
	if (zVert > max.z)
	  max.z = zVert;
    }
}

const float* Mesh::getVertices() {
    return &Vertices[0];
}

int Mesh::getNumVertices(void) {
    return Vertices.size();
}

glm::vec3* Mesh::getMax(void) {
  return &max;
}

glm::vec3* Mesh::getMin(void) {
  return &min;
}
