#pragma once
#include <fstream>
#include <iostream>
#include "Entity.h"

class EntityFileHandler {
 public:
    void LoadEntities(std::vector<Entity*> &entities);
    bool SaveEntity(int entityID);
    
 private:
    const char* obj_ext = ".obj";
    const char* obj_dir = ".\\Data\\Objects\\";
    const char* obj_ls_dir = ".\\Data\\Listings\\Entities.txt";
};
