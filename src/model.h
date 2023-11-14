

#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h> 

#include "mesh.h"
#include "shader.h"

#include <string>
#include <map>
#include <vector>

class Model
{
public:
    // model data 
    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh>    meshes;
    std::string directory;
    bool gammaCorrection;

    // constructor, expects a filepath to a 3D model.
    Model(bool gamma = false);

    // draws the model, and thus all its meshes
    void Draw(Shader &shader);
};

#endif

