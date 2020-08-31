#pragma once
#include <string>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

class GL_Context {
 public:
    GL_Context(int width, int height, const std::string windowName);
    GLFWwindow* getWindow(void);
    void Clear(void);
    void Swap(void);
    void Poll(void);
    void Terminate(void);
    bool ExitWindow(void);

    
 private:
    GLFWwindow* window;

    bool Init(int width, int height, const std::string windowName);
};
