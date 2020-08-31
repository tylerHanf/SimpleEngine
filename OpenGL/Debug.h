#pragma once
#include <string>
#include <iostream>
#include <fstream>

/*
This class handles error logging/printing
*/
class Debug {
 public:
    static Debug& Instance();

    void Log(const std::string error);
    void PrintError(const std::string error);
    void PrintError(float val);
    void PrintGLFWError();

    char** glfwErrorCode;
    
 private:
    const std::string filePath;
    Debug();
};
