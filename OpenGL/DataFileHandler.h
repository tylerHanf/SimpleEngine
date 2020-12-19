#pragma once
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Debug.h"

struct meshData {
  std::string meshName;
  std::vector<float> vertData;
  unsigned char* textData = 0;
  unsigned int textID;  
  int textWidth=0;
  int textHeight=0;
};

class DataFileHandler {
 public:
  DataFileHandler();
  void LoadMeshes(void);
  void GetVertices(meshData* newMesh, const char* meshFileName);
  std::vector<meshData> GetObjectData(void);
  void SetTextID(int meshIdx, int textureID);
  meshData* GetMesh(int meshIdx);
  int NumMeshes(void);
  int NumTextures(void);
    
 private:
  // Entity filepaths
  std::vector<meshData> objectData;
  int numTextures = 0;
  int numMeshes = 0;
  //std::vector<unsigned char*> textures;
  const char* mesh_ext = ".obj";
  const char* material_ext = ".mtl";
  const char* mesh_dir = ".\\Data\\Objects\\";
  const char* mesh_ls_dir = ".\\Data\\Listings\\Meshes.txt";
};
