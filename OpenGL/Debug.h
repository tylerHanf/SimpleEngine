#pragma once
#include <string>
#include <vector>
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
  void PrintMeshData(std::vector<float> meshData);
  char** glfwErrorCode;
    
 private:
    const std::string filePath;
    Debug();
};
