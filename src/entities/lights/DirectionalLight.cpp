#include "entities/lights/DirectionalLight.hpp"

DirectionalLight::DirectionalLight(
    std::string name, const glm::vec3& direction, const glm::vec3& color
) :
    Entity(name)
{
    this->direction = direction;
    this->color = glm::vec4(color, 1.0f);
}

void DirectionalLight::update(Shader& shader) {
    shader.setUniform(name + ".direction", direction);
    shader.setUniform(name + ".color", color);
}
