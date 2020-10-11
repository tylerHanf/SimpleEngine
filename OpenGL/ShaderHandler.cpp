#include "ShaderHandler.h"

void ShaderHandler::AddShader(const char* vertp, const char* fragp) {
    Shader* newShader = new Shader(vertp, fragp, S_Type(BASIC));
    shaders.push_back(newShader);
    curProg = shaders[0]->GetHandle();
    curShader = shaders[0];
}

void ShaderHandler::SetMat4Uniform(Uniform loc, glm::mat4 val) {
    curShader->SetMat4Uniform(loc, val);
}

void ShaderHandler::SetVec3Uniform(Uniform loc, glm::vec3 val) {
    curShader->SetVec3Uniform(loc, val);
}

GLuint ShaderHandler::GetCurProg() {
    return curProg;
}

void ShaderHandler::Use(int idx) {
    curShader = shaders[idx];
    curProg = curShader->GetHandle();
}
