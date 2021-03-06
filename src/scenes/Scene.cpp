#include <glm/glm.hpp>

#include "scenes/Scene.hpp"
#include "scenes/Forest.hpp"
#include "entities/lights/AmbientLight.hpp"
#include "entities/lights/DirectionalLight.hpp"

Scene::Scene(GLuint width, GLuint height) :
    player(
        glm::vec3(20.0f, 0.0f, 0.0f), // position
        0.2f                          // speed
    ),
    attack(player),
    camera(
        glm::vec3(0.0f, 10.0f, -10.0f), // position
        player.getPosition(),           // target
        glm::vec3(0.0f, 10.0f, 0.0f),   // target offset
        glm::radians(45.0f),            // fov
        width, height,                  // width & height
        0.1f, 1000.0f                   // zNear & zFar
    ),
    skybox(),
    forest(300.0f, 50) // radius, nTrees
{
    // forest
    auto& forestBgObjs = forest.getBgObjects();
    bgObjects.reserve(forestBgObjs.size());
    for (auto* o : forestBgObjs) { bgObjects.push_back(o); }

    // lights
    lights.push_back(std::make_shared<AmbientLight>(
        "aL",                       // name
        glm::vec3(0.1f, 0.0f, 0.0f) // color
    ));

    lights.push_back(std::make_shared<DirectionalLight>(
        "dL",                         // name
        glm::vec3(1.0f, -0.5f, 0.0f), // direction
        glm::vec3(0.9f, 0.7f, 0.7f)   // color
    ));

    lights.push_back(std::make_shared<PointLight>(
        "pL",                           // name
        glm::vec3(20.0f, 10.0f, 10.0f), // position
        glm::vec3(0.9f, 0.57f, 0.16f),  // color
        0.1f,                           // constant
        0.09f,                          // linear
        0.01f                           // quadratic
    ));

    // Collidables
    collidables.reserve(bgObjects.size());
    for (auto* c : bgObjects) { collidables.push_back(c); }

    // Renderers
    playerRenderer = std::make_unique<PlayerRenderer>(
        player, camera, lights
    );
    attackRenderer = std::make_unique<AttackRenderer>(
        attack, camera, lights
    );
    bgObjectsRenderer = std::make_unique<BgObjectsRenderer>(
        bgObjects, camera, lights
    );
    skyboxRenderer = std::make_unique<SkyboxRenderer>(
        skybox, camera
    );
    streamRenderer = std::make_unique<StreamRenderer>(
        forest.getRiver(), forest.getWaterfall(), camera, lights
    );
    fireRenderer = std::make_unique<FireRenderer>(
        forest.getFire(), camera
    );
}

void Scene::update() {
    // logic
    player.move();
    for (auto* c : collidables) {
        if (player.collide(*c)) {
            player.cancelMove();
            break;
        }
    }

    camera.setTarget(player.getPosition());

    attack.update();

    forest.update();

    // render
    playerRenderer->render();
    attackRenderer->render();
    bgObjectsRenderer->render();
    skyboxRenderer->render();
    streamRenderer->render();
    fireRenderer->render();
}
