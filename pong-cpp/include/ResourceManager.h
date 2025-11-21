#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include "Shader.h"

class ResourceManager {
public:
    static std::map<std::string, Shader> Shaders;

    static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name);
    static Shader& GetShader(std::string name);
    static void Clear();
private:
    ResourceManager() { }
    static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile);
};

#endif