

#include "sprite_renderer.h"


SpriteRenderer::SpriteRenderer(Shader &shader)
{
    this->shader = shader;
    this->nextID = 1;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

unsigned int SpriteRenderer::Draw(Texture2D &texture, glm::mat4 model, glm::vec3 color, unsigned int ID)
{
    // this->shader.Use();
    // this->shader.SetMatrix4("model", model);
    // this->shader.SetVector3f("spriteColor", color);

    // glActiveTexture(GL_TEXTURE0);
    // texture.Bind();

    spriteData sprite;
    sprite.texture = &texture;
    sprite.model = model;
    sprite.color = color;
    if (ID == 0) {
        this->renderMap[this->nextID] = sprite;
        return this->nextID++;
    } else {
        this->renderMap[ID] = sprite;
        return ID;
    }
}

void SpriteRenderer::Render(bool wipeMap)
{
    if ( this->renderMap.empty() )
        return;
    
    this->shader.Use();

    // always set the optional uniforms for the first processed element
    const auto &[firstID, firstSprite] = *this->renderMap.begin();
    unsigned int lastTexture = firstSprite.texture->ID;
    glm::vec3 lastColor = firstSprite.color;
    glActiveTexture(GL_TEXTURE0);
    firstSprite.texture->Bind();
    this->shader.SetVector3f("spriteColor", lastColor);

    for (auto &[id, sprite] : this->renderMap)
    {
        this->shader.SetMatrix4("model", sprite.model);

        if (sprite.texture->ID != lastTexture) {
            glActiveTexture(GL_TEXTURE0);
            sprite.texture->Bind();
        }
        lastTexture = sprite.texture->ID;

        if (sprite.color != lastColor) {
            this->shader.SetVector3f("spriteColor", sprite.color);
        }
        lastColor = sprite.color;

        glBindVertexArray(this->quadVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }

    if (wipeMap)
        this->WipeRenderMap();
}

void SpriteRenderer::WipeRenderMap()
{
    this->renderMap.clear();
    this->nextID = 1;
}

void SpriteRenderer::StopDrawing(unsigned ID)
{
    this->renderMap.erase(ID);
    if (ID == this->nextID-1)
    {
        if (this->renderMap.empty())
        {
            this->nextID = 1;
        } else {
            this->nextID = this->renderMap.rbegin()->first + 1;
        }
    }
}

void SpriteRenderer::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = { 
        // y coordinates are flipped because loaded textures are flipped
        // pos      // tex
        0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

