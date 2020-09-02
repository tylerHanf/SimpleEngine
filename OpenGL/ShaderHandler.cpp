#include "ShaderHandler.h"
#include <fstream>

/*
Show the program log (linking)
*/
void ShaderHandler::printProgramLog(int prog) {
    int len = 0;
    int chWrittn = 0;
    char *log;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
	log = (char *)malloc(len);
	glGetProgramInfoLog(prog, len, &chWrittn, log);
	std::cout << "Program Info Log: " << log << std::endl;
	free(log);
    }
}

/*
Show the shader log
*/
void ShaderHandler::printShaderLog(GLuint shader) {
    int len = 0;
    int chWrittn = 0;
    char *log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
	log = (char*)malloc(len);
	glGetShaderInfoLog(shader, len, &chWrittn, log);
	std::cout << "Shader Info Log: " << log << std::endl;
	free(log);
    }
}

/*
Determine if there is an error
*/
bool ShaderHandler::checkOpenGLError(void) {
    bool foundError = false;
    int glErr = glGetError();
    while (glErr != GL_NO_ERROR) {
	std::cout << "glError: " << glErr << std::endl;
	foundError = true;
	glErr = glGetError();
    }
    return foundError;
}

/*
Read in shader source code from file
*/
std::string ShaderHandler::readShaderSource(const char *filepath) {
    std::string content;
    std::ifstream fileStream(filepath, std::ios::in);
    std::string line = "";
    while (!fileStream.eof()) {
	getline(fileStream, line);
	content.append(line + "\n");
    }
    fileStream.close();
    return content;
}

/*
Create shader program with vertex and frag shader
*/
GLuint ShaderHandler::createShaderProgram(const char *vp, const char *fp) {
    GLint vertCompiled;
    GLint fragCompiled;
    GLint linked;

    std::string vshaderSourceStr = readShaderSource(vp);
    std::string fshaderSourceStr = readShaderSource(fp);

    const char *vshaderSource = vshaderSourceStr.c_str();
    const char *fshaderSource = fshaderSourceStr.c_str();

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);

    glCompileShader(vShader);

    checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if (vertCompiled != 1) {
	std::cout << "vertex compilation failed" << std::endl;
	printShaderLog(vShader);
    }

    glCompileShader(fShader);
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if (fragCompiled != 1) {
	std::cout << "fragment compilation failed" << std::endl;
	printShaderLog(fShader);
    }

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);
    glLinkProgram(vfProgram);

    checkOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if (linked != 1) {
	std::cout << "linking failed" << std::endl;
	printProgramLog(vfProgram);
    }

    return vfProgram;
}
