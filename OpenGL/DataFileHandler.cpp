#include "DataFileHandler.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>

#define STB_IMAGE_IMPLEMENTATION
#include <STB_IMAGE/stb_image.h>

DataFileHandler::DataFileHandler() {
  LoadMeshes();
}

void DataFileHandler::LoadMeshes(void) {
    char data[100];
    char temp[50];
    std::string meshFile;
    std::ifstream reader;
    //    meshData* newMesh;

    float x,y,z = 0.0;
    reader.open(mesh_ls_dir);
    if (!reader.is_open()) 
	Debug::Instance().PrintError("Failed to open Mesh file");
    else {
	while (!reader.eof()) {
        	  meshData newMesh;
	  numMeshes++;
	  reader.getline(data, 100);
	  sscanf_s(data, "%s %f,%f,%f", temp, 50, &x, &y, &z);
	  meshFile = temp;
	  newMesh.meshName = temp;
	  meshFile.insert(0, mesh_dir);
	  meshFile.append(mesh_ext);
	  GetVertices(&newMesh, meshFile.c_str());
	   meshFile = "";	    
	}
    }
}

void DataFileHandler::GetVertices(meshData* newMesh, const char* meshFileName) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(meshFileName, aiProcess_Triangulate);

    if (!scene) {
	Debug::Instance().PrintError("Failed to read mesh from file");
    }

    if (scene->mMaterials[1]->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
      aiString texturePath;
      scene->mMaterials[1]->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
      int width, height, channels;
      unsigned char* texData = NULL;
      newMesh->textData = stbi_load(texturePath.C_Str(), &width, &height, &channels, 0);
      if (newMesh->textData) {
	newMesh->textWidth = width;
	newMesh->textHeight = height;
	numTextures++;
      }
      else {
	Debug::Instance().PrintError("Failed to load texture");
      }
    }

    float xVert, yVert, zVert,
          xNorm, yNorm, zNorm,
          xText, yText;
      
    for (int i=0; i<scene->mMeshes[0]->mNumVertices; i++) {
      xVert = scene->mMeshes[0]->mVertices[i].x;
      yVert = scene->mMeshes[0]->mVertices[i].y;
      zVert = scene->mMeshes[0]->mVertices[i].z;
	
      xNorm = scene->mMeshes[0]->mNormals[i].x;
      yNorm = scene->mMeshes[0]->mNormals[i].y;
      zNorm = scene->mMeshes[0]->mNormals[i].z;
	
      xText = scene->mMeshes[0]->mTextureCoords[0][i].x;
      yText = scene->mMeshes[0]->mTextureCoords[0][i].y;
	
      newMesh->vertData.push_back(xVert); newMesh->vertData.push_back(yVert);
      newMesh->vertData.push_back(zVert); newMesh->vertData.push_back(xNorm);
      newMesh->vertData.push_back(yNorm); newMesh->vertData.push_back(zNorm);
      newMesh->vertData.push_back(xText); newMesh->vertData.push_back(yText); 
    }
    objectData.push_back(*newMesh);
}

std::vector<meshData> DataFileHandler::GetObjectData(void) {
  return objectData; 
}

void DataFileHandler::SetTextID(int meshIdx, int textureID) {
  objectData[meshIdx].textID = textureID;
}

meshData* DataFileHandler::GetMesh(int meshIdx) {
  return &(objectData[meshIdx]);
}

int DataFileHandler::NumMeshes(void) {
  return numMeshes;
}

int DataFileHandler::NumTextures(void) {
  return numTextures;
}
