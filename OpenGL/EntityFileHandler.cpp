#include "EntityFileHandler.h"
#include "Debug.h"

void EntityFileHandler::LoadEntities(std::vector<Entity*> &entities) {
    char data[100];
    std::string objFile;
    std::ifstream reader;
    float x,y,z;
    int objSize;
    reader.open(obj_ls_dir);
    if (!reader.is_open()) 
	Debug::Instance().PrintError("Failed to open Entity file");
    else {
	while (!reader.eof()) {
	    reader.getline(data, 100);
	    for (int i=0; i<sizeof(data); i++) {
		if (data[i] == ' ')
		    break;
		objFile.push_back(data[i]);
	    }
	    
	    objSize = objFile.size()+1;
	    objFile.insert(0, obj_dir);
	    objFile.append(obj_ext);
	    
	    x = (float)(data[objSize]-'0');
	    y = (float)(data[objSize+2]-'0');
	    z = (float)(data[objSize+4]-'0');
	    Entity* newEntity = new Entity(objFile.c_str(), glm::vec3(x, y, z));
	    entities.push_back(newEntity);
	}
    }
}

