#pragma once
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "EntityHandler.h"
#include "ShaderHandler.h"
#include "Debug.h"

class DataFileHandler {
 public:
    DataFileHandler(EntityHandler *ents, ShaderHandler *shads);
    bool SaveEntity(int entityID);
    
 private:
    EntityHandler* entities;
    ShaderHandler* shaders;

    void LoadEntities(void);
    
    // Entity filepaths
    const char* obj_ext = ".obj";
    const char* obj_dir = ".\\Data\\Objects\\";
    const char* obj_ls_dir = ".\\Data\\Listings\\Entities.txt";
};
