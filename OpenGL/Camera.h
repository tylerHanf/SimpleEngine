#pragma once
#include <GLM/glm.hpp>

class Camera {
 public:
    Camera(glm::vec3 location);
    

 private:
    glm::vec3 location;
};
