#include "Mesh.h"
#include "Debug.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/*
Contains Mesh data (currently just vertices and normals)
*/
Mesh::Mesh(const std::string& filename) {
    Assimp::Importer importer;
    Debug::Instance().PrintError(filename);
    const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate);

    if (!scene) {
	Debug::Instance().PrintError("Failed to read mesh from file");
    }

    float xVert, yVert, zVert;
    for (int i=0; i<scene->mMeshes[0]->mNumVertices; i++) {
        xVert = scene->mMeshes[0]->mVertices[i].x;
	yVert = scene->mMeshes[0]->mVertices[i].y;
	zVert = scene->mMeshes[0]->mVertices[i].z;
	
	Vertices.push_back(xVert);
	Vertices.push_back(yVert);
	Vertices.push_back(zVert);
	Vertices.push_back(scene->mMeshes[0]->mNormals[i].x);
	Vertices.push_back(scene->mMeshes[0]->mNormals[i].y);
	Vertices.push_back(scene->mMeshes[0]->mNormals[i].z);

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
