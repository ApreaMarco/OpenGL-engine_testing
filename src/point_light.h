

#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader.h"

#include <string>
#include <map>

// default values
const glm::vec3 AMBIENT(0.0f);
const glm::vec3 DIFFUSE(0.8f);
const glm::vec3 SPECULAR(1.0f);
const float CONSTANT = 1.0f;
const float LINEAR = 0.09f;
const float QUADRATIC = 0.032f;

class PointLight
{
    private:
        static std::map<int, PointLight*> instanceMap;
        static int instanceCount;
        int id;

        // set uniforms
        void setUniforms(Shader &shader, int lightNumber);

    public:
        // attributes
        glm::vec3 Position;
        glm::vec3 Ambient;
        glm::vec3 Diffuse;
        glm::vec3 Specular;
        float Constant;
        float Linear;
        float Quadratic;

        // constructor
        PointLight(glm::vec3 position, glm::vec3 ambient = AMBIENT, glm::vec3 diffuse = DIFFUSE, glm::vec3 specular = SPECULAR,
                    float constant = CONSTANT, float linear = LINEAR, float quadratic = QUADRATIC);

        // set uniforms
        static void setAllUniforms(Shader &shader);
};

#endif

