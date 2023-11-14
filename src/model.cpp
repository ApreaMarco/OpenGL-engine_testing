

#include "model.h"

// constructor
Model::Model(bool gamma)
    : gammaCorrection(gamma) {}

// draws the model, and thus all its meshes
void Model::Draw(Shader &shader)
{
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(shader);
}

