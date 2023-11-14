

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <glad/glad.h>
#include <assimp/scene.h>

#include "texture.h"
#include "shader.h"
#include "model.h"
#include "config.h"

#include <map>
#include <string>

// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no 
// public constructor is defined.
class ResourceManager
{
public:
    // resource storage
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;
    static std::map<std::string, Model>     Models;
    static std::map<std::string, Config>    Configs;
    // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader    LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
    // retrieves a stored sader
    static Shader    GetShader(std::string name);
    // loads (and generates) a texture from file
    static Texture2D LoadTexture(const char *file, std::string name);
    // retrieves a stored texture
    static Texture2D GetTexture(std::string name);
    // loads (and generates) a model class from file
    static Model     LoadModel(const char *file, std::string name);
    // retrieves a stored model
    static Model     GetModel(std::string name);
    // loads (and generates) a config class from file
    static Config    LoadConfig(const char *file, std::string name);
    // retrieves a stored config
    static Config    GetConfig(std::string name);
    // updates a stored config
    static void      UpdateConfig(Config config, std::string name);
    // saves a stored config to a file
    static void      SaveConfig(const char *file, std::string name);
    // properly de-allocates all loaded resources
    static void      Clear();
private:
    // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() { }
    // loads and generates a shader from file
    static Shader    loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
    // loads a single texture from file
    static Texture2D loadTextureFromFile(const char *file);
    // loads and generates a model from file
    static Model     loadModelFromFile(const char *file);
    static void      processNode(Model* model, aiNode *node, const aiScene *scene);
    static Mesh      processMesh(Model* model, aiMesh *mesh, const aiScene *scene);
    static std::vector<Texture> loadMaterialTextures(Model* model, aiMaterial *mat, aiTextureType type, std::string typeName);
    // loads and generates a config from file
    static Config    loadConfigFromFile(const char *file);
    // saves config to a file
    static void      saveConfigToFile(const char *file, Config config);
};

#endif

