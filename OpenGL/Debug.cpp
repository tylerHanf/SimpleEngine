#include "Debug.h"

Debug::Debug() :
filePath("log.txt")
{}

Debug& Debug::Instance() {
    static Debug debugObj;
    return debugObj;
}

void Debug::Log(const std::string error) {
    std::fstream errorFile;
    errorFile.open(filePath);
    errorFile << error << "\n";
    errorFile.close();
}

void Debug::PrintError(const std::string error) {
    std::cout << error << std::endl;
}

void Debug::PrintError(float val) {
    std::cout << val << std::endl;
}

void Debug::PrintGLFWError() {
    std::cout << glfwErrorCode << std::endl;
}
