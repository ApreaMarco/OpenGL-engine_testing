

#include "billboard.h"


Billboard::Billboard(Texture2D texture, glm::vec3 pos, glm::vec2 size, glm::vec3 color) 
    : Texture(texture), Position(pos), Size(size), Color(color) { }

Billboard::~Billboard()
{
    
}

void Billboard::Draw(Shader &shader)
{
    // shader.Use();
    // shader.SetMatrix4("model", this->getModelMatrix());
    // shader.SetVector3f("spriteColor", Color);

    // glActiveTexture(GL_TEXTURE0);
    // this->Texture.Bind();

    // glBindVertexArray(OH_NO);
    // glDrawArrays(GL_POINTS, 0, 1);
    // glBindVertexArray(0);
}

glm::mat4 Billboard::getModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, Position);
    model = glm::scale(model, glm::vec3(Size, 1.0f));
    return model;
}

