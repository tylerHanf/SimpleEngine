#pragma once
#include <string>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>

class GL_Context {
 public:
    GL_Context(int width, int height, const std::string windowName);
    GLFWwindow* getWindow(void);
    void ClearDepthBuffer(void);
    void ClearColorBuffer(void);
    void UseProgram(GLuint renderingProgram);
    GLuint GetUniformLocation(GLuint renderingProgram, const char* varName);
    void GetFrameBufferSize(int* width, int* height);
    void Swap(void);
    void Poll(void);
    void Terminate(void);
    bool ExitWindow(void);
    void SetMatrix4fv(GLuint varLoc, glm::mat4 value);
    double GetTime(void);

 private:
    GLFWwindow* window;

    bool Init(int width, int height, const std::string windowName);
};
