#include "DataFileHandler.h"

DataFileHandler::DataFileHandler(EntityHandler* ents, ShaderHandler* shads) {
    entities = ents;
    shaders = shads;

    LoadEntities();
}

void DataFileHandler::LoadEntities(void) {
    char data[100];
    char temp[50];
    std::string objFile;
    std::ifstream reader;
    float x,y,z = 0.0; 
    reader.open(obj_ls_dir);
    if (!reader.is_open()) 
	Debug::Instance().PrintError("Failed to open Entity file");
    else {
	while (!reader.eof()) {
	    reader.getline(data, 100);
	    sscanf_s(data, "%s %f,%f,%f", temp, 50, &x, &y, &z);
	    
	    objFile = temp;
	    objFile.insert(0, obj_dir);
	    objFile.append(obj_ext);

	    entities->AddEntity(objFile.c_str(), glm::vec3(x,y,z));
	    objFile = "";
	}
    }
}
