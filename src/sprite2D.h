

#ifndef SPRITE2D_H
#define SPRITE2D_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"

class Sprite2D
{
private:
    unsigned int ID;
    SpriteRenderer* Renderer;
public:
    // object state
    glm::vec2 Position, Size;
    float Rotation;

    // render state
    Texture2D Texture;
    glm::vec3 Color;
    
    // constructor
    Sprite2D(SpriteRenderer* renderer, Texture2D texture, glm::vec2 pos = glm::vec2(0.0f), glm::vec2 size = glm::vec2(1.0f), float rotation = 0.0f, glm::vec3 color = glm::vec3(1.0f));
    // destructor
    ~Sprite2D();
    
    // methods
    void ChangeRenderer(SpriteRenderer* renderer);
    void Draw();
    void DrawOnTop();
    void StopDrawing();
    glm::mat4 getModelMatrix();
};

#endif

