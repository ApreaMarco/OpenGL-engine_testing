

#include "transform.h"

#include <glm/gtc/matrix_transform.hpp>


Transform::Transform(glm::vec3 pos, glm::vec3 size, glm::vec3 rotation)
    : Position(pos), Size(size), Rotation(rotation) { }

glm::mat4 Transform::getModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, Position);
    model = glm::scale(model, Size);
    model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
    return model;
}

