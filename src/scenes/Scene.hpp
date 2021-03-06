#ifndef SCENES_HPP
#define SCENES_HPP

#include <vector>
#include <memory>

#include "scenes/Forest.hpp"
#include "entities/Entity.hpp"
#include "entities/player/Player.hpp"
#include "entities/player/Attack.hpp"
#include "entities/camera/Camera.hpp"
#include "entities/skybox/Skybox.hpp"
#include "entities/objects/BgObject.hpp"
#include "behaviours/collisions/Collidable.hpp"
#include "renderers/PlayerRenderer.hpp"
#include "renderers/AttackRenderer.hpp"
#include "renderers/BgObjectsRenderer.hpp"
#include "renderers/SkyboxRenderer.hpp"
#include "renderers/StreamRenderer.hpp"
#include "renderers/FireRenderer.hpp"

class Scene {
public:
    Scene(GLuint width, GLuint height);
    
    void update();
    
private:
    std::vector<std::shared_ptr<Entity>> lights;
    std::vector<Collidable*> collidables;
    std::vector<BgObject*> bgObjects;
    Player player;
    Attack attack;
    Camera camera;
    Skybox skybox;
    Forest forest;
    
    std::unique_ptr<PlayerRenderer> playerRenderer;
    std::unique_ptr<AttackRenderer> attackRenderer;
    std::unique_ptr<BgObjectsRenderer> bgObjectsRenderer;
    std::unique_ptr<SkyboxRenderer> skyboxRenderer;
    std::unique_ptr<StreamRenderer> streamRenderer;
    std::unique_ptr<FireRenderer> fireRenderer;
};

#endif // SCENES_HPP
