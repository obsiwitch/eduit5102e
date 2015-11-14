#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "models/Model.hpp"
#include "entities/Entity.hpp"
#include "entities/player/PlayerEventHandler.hpp"
#include "collisions/BoundingBox.hpp"

class Player : public Entity {
public:
    Player(const glm::vec3& position, float speed);
    
    void update(Shader& shader) override;
    
    PlayerEventHandler& getEventHandler();
    glm::vec3 getPosition();
    BoundingBox getBoundingBox();
    
private:
    Model model;
    float speed;
    BoundingBox boundingBox;
    PlayerEventHandler eventHandler;
    
    void move();
};

#endif // PLAYER_HPP
