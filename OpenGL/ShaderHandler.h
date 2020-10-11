#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Shader.h"


/*
Handles all shader reader and loading
*/
class ShaderHandler {
 public:
    void AddShader(const char* vertp, const char* fragp);
    void SetMat4Uniform(Uniform loc, glm::mat4 val);
    void SetVec3Uniform(Uniform loc, glm::vec3 val);
    GLuint GetCurProg(void);
    void Use(int idx);
    
 private:
    GLuint curProg;
    Shader* curShader;
    std::vector<Shader*> shaders;

};
