

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>

#include "texture.h"
#include "shader.h"


struct spriteData {
    Texture2D* texture;
    glm::mat4 model;
    glm::vec3 color;
};

class SpriteRenderer
{
public:
    // Constructor (inits shaders/shapes)
    SpriteRenderer(Shader &shader);
    // Destructor
    ~SpriteRenderer();
    // Renders a defined quad textured with given sprite
    unsigned int Draw(Texture2D &texture, glm::mat4 model, glm::vec3 color = glm::vec3(1.0f), unsigned int ID = 0);
    void Render(bool wipeMap = false);
    void WipeRenderMap();
    void StopDrawing(unsigned ID);
private:
    // Render state
    Shader       shader;
    unsigned int quadVAO;
    unsigned int nextID;
    std::map<unsigned int, spriteData> renderMap;
    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
};

#endif

