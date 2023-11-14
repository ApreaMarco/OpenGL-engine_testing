

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glad/glad.h>
#include <glm/glm.hpp>

class Transform
{
public:
    glm::vec3 Position, Size, Rotation;
    Transform(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f));
    glm::mat4 getModelMatrix();
};

#endif

