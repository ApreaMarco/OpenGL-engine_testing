

#include "sprite2D.h"

#include <glm/gtc/matrix_transform.hpp>


Sprite2D::Sprite2D(SpriteRenderer* renderer, Texture2D texture, glm::vec2 pos, glm::vec2 size, float rotation, glm::vec3 color) 
    : Renderer(renderer), Texture(texture), Position(pos), Size(size), Rotation(rotation), Color(color)
{
    this->ID = 0;
}

Sprite2D::~Sprite2D()
{
    
}

void Sprite2D::ChangeRenderer(SpriteRenderer* renderer)
{
    this->StopDrawing();
    this->Renderer = renderer;
}

void Sprite2D::Draw()
{
    this->ID = this->Renderer->Draw(this->Texture, this->getModelMatrix(), this->Color, this->ID);
}

void Sprite2D::DrawOnTop()
{
    this->StopDrawing();
    this->Draw();
}

void Sprite2D::StopDrawing()
{
    this->Renderer->StopDrawing(this->ID);
    this->ID = 0;
}

glm::mat4 Sprite2D::getModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(Position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)
    model = glm::translate(model, glm::vec3(0.5f * Size.x, 0.5f * Size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(Rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * Size.x, -0.5f * Size.y, 0.0f)); // move origin back
    model = glm::scale(model, glm::vec3(Size, 1.0f)); // last scale
    return model;
}

