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
    const aiScene* scene = importer.ReadFile(filename, 0);

    if (!scene) {
	Debug::Instance().PrintError("Failed to read mesh from file");
    }

    for (int i=0; i<scene->mMeshes[0]->mNumVertices; i++) {
	Vertices.push_back(scene->mMeshes[0]->mVertices[i].x);
	Vertices.push_back(scene->mMeshes[0]->mVertices[i].y);
	Vertices.push_back(scene->mMeshes[0]->mVertices[i].z);

	Normals.push_back(scene->mMeshes[0]->mNormals[i].x);
	Normals.push_back(scene->mMeshes[0]->mNormals[i].y);
	Normals.push_back(scene->mMeshes[0]->mNormals[i].z);
    }
}

std::vector<float>& Mesh::getVertices() {
    return Vertices;
}

std::vector<float>& Mesh::getNormals() {
    return Normals;
}
