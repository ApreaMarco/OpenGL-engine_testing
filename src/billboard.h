

#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <glad/glad.h>

#include "texture.h"
#include "shader.h"

class Billboard
{
public:
    // object state
    glm::vec3 Position;
    glm::vec2 Size;

    // render state
    Texture2D Texture;
    glm::vec3 Color;
    
    // constructor
    Billboard(Texture2D texture, glm::vec3 pos = glm::vec3(0.0f), glm::vec2 size = glm::vec2(1.0f), glm::vec3 color = glm::vec3(1.0f));
    // destructor
    ~Billboard();
    
    // methods
    void Draw(Shader &shader);
    glm::mat4 getModelMatrix();
};

#endif

