#include "Shader.h"

#include <iostream>
#include <fstream>
#include <GLM/gtc/type_ptr.hpp>
#include "Debug.h"

/*
Check if different types have constant uniforms
*/
Shader::Shader(const char* vertp, const char* fragp, S_Type i_type) :
    type(i_type)
{
    createShaderProgram(vertp, fragp);
    setupUniforms();
}

GLuint Shader::GetHandle() {
    return handler;
}

void Shader::SetMat4Uniform(Uniform loc, glm::mat4 val) {
    switch (loc) {
    case MODEL:
	GL_SetMat4(basic.model, val);
	break;
    case VIEW:
	GL_SetMat4(basic.view, val);
	break;
    case PROJECTION:
	GL_SetMat4(basic.projection, val);
	break;
    default:
	Debug::Instance().PrintError("Failed to set mat4, Uniform not found");
    }
}

void Shader::SetVec3Uniform(Uniform loc, glm::vec3 val) {
    switch (loc) {
    case E_COLOR:
	GL_SetVec3(basic.objColor, val);
	break;
    case L_POS:
	GL_SetVec3(light.lightPos, val);
	break;
    case L_COLOR:
	GL_SetVec3(light.lightColor, val);
	break;
    default:
	Debug::Instance().PrintError("Failed to set vec3, Uniform not found");
    }
}

void Shader::GL_SetMat4(GLuint loc, glm::mat4 val) {
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::GL_SetVec3(GLuint loc, glm::vec3 val) {
    glUniform3fv(loc, 1, glm::value_ptr(val));
}


/*
Show the program log (linking)
*/
void Shader::printProgramLog(int prog) {
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
void Shader::printShaderLog(GLuint shader) {
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
bool Shader::checkOpenGLError(void) {
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
std::string Shader::readShaderSource(const char *filepath) {
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
void Shader::createShaderProgram(const char *vp, const char *fp) {
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

    handler = vfProgram;
}

void Shader::setupUniforms(void) {
    int count = 0;
    const GLsizei size = 32;
    GLchar name[size];
    GLenum *type = 0;
    GLint act_size = 0;
    GLuint uLoc = 0;
    glGetProgramiv(handler, GL_ACTIVE_UNIFORMS, &count);
    for (int i=0; i<count; i++) {
	glGetActiveUniform(handler, (GLuint)i, size, NULL, &act_size, type, name);
	uLoc = glGetUniformLocation(handler, name);
	if (!std::strcmp(name, "model")) {
	    basic.model = uLoc;
	}
	else if (!std::strcmp(name, "view")) {
	    basic.view = uLoc;
	}
	else if (!std::strcmp(name, "projection")) {
	    basic.projection = uLoc;
	}
	else if (!std::strcmp(name, "objColor")) {
	    basic.objColor = uLoc;
	}
	else if (!std::strcmp(name, "lightPos")) {
	    light.lightPos = uLoc;
	}
	else if (!std::strcmp(name, "lightColor")) {
	    light.lightColor = uLoc;
	}
	else {
	    Debug::Instance().PrintError("Unknown Uniform:");
	    Debug::Instance().PrintError(name);
	}
    }
}
