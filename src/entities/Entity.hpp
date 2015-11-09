#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <glm/glm.hpp>

#include "shaders/Shader.hpp"

class Entity {
public:
    Entity(std::string name, const glm::vec3& position);
    
    /**
     * Updates this Entity's state, and update uniforms linked to this
     * entity with the specified shader. The shader should be bound before
     * calling this method.
     */
    virtual void update(Shader& shader) = 0;
    
protected:
    std::string name;
    glm::vec3 position;
};

#endif // ENTITY_HPP
