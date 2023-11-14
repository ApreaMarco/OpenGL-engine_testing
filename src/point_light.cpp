

#include "point_light.h"

#include <glm/gtc/matrix_transform.hpp>

// instantiate static variables
int PointLight::instanceCount = 0;
std::map<int, PointLight*> PointLight::instanceMap;


// constructor
PointLight::PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse,
    glm::vec3 specular, float constant, float linear, float quadratic)
{
    id = instanceCount;
    instanceMap[id] = this;
    instanceCount++;
    Position = position;
    Ambient = ambient;
    Diffuse = diffuse;
    Specular = specular;
    Constant = constant;
    Linear = linear;
    Quadratic = quadratic;
}

// set uniforms
// i could use cleaner code if I had the format header
void PointLight::setUniforms(Shader &shader, int lightNumber)
{
    std::string strNumber = std::to_string(lightNumber);
    shader.SetVector3f(("pointLights[" + strNumber + "].position").c_str(), Position);
    shader.SetVector3f(("pointLights[" + strNumber + "].ambient").c_str(), Ambient);
    shader.SetVector3f(("pointLights[" + strNumber + "].diffuse").c_str(), Diffuse);
    shader.SetVector3f(("pointLights[" + strNumber + "].specular").c_str(), Specular);
    shader.SetFloat(("pointLights[" + strNumber + "].constant").c_str(), Constant);
    shader.SetFloat(("pointLights[" + strNumber + "].linear").c_str(), Linear);
    shader.SetFloat(("pointLights[" + strNumber + "].quadratic").c_str(), Quadratic);
}

void PointLight::setAllUniforms(Shader &shader)
{
    for (int i=0; i<instanceCount; i++)
    {   
        instanceMap[i]->setUniforms(shader, i);
    }
    shader.SetInt("nr_point_lights", instanceCount);
}

