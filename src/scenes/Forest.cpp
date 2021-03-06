#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "scenes/Forest.hpp"

Forest::Forest(float radius, unsigned int nTrees) :
    ground(
        "resources/ground/ground.obj", // file path
        glm::vec3(0.0f),               // position
        glm::vec3(1.0f),               // scale
        BoundingBox(
            glm::vec3(0.0f),
            glm::vec3(0.0f)
        )
    ),
    torch(
        "resources/staff/staff.obj",   // file path
        glm::vec3(20.0f, 0.0f, 10.0f), // position
        glm::vec3(5.0f),               // scale
        BoundingBox(                   // bounding box
            glm::vec3(-0.5f),
            glm::vec3(0.5f)
        )
    ),
    waterfall(
        "resources/waterfall/waterfall.obj", // file path
        glm::vec3(0.0f, 0.0f, radius),       // position
        glm::vec3(1.0f),                     // scale
        BoundingBox(glm::vec3(0.0f), glm::vec3(0.0f))
    ),
    river(
        "resources/river/river.obj",   // file path
        glm::vec3(0.0f, 0.1f, radius), // position
        glm::vec3(1.0f),               // scale
        BoundingBox(glm::vec3(0.0f), glm::vec3(0.0f))
    ),
    fire(
        "resources/fire/fire.obj",     // file path
        glm::vec3(20.0f, 9.5f, 10.0f), // position
        glm::vec3(0.5f, 0.7f, 0.5f),   // scale
        BoundingBox(glm::vec3(0.0f), glm::vec3(0.0f))
    ),
    radius(radius),
    randomGen(std::time(0))
{
    createCliffs();
    generateTrees(nTrees);

    bgObjects.reserve(2 + cliffs.size() + trees.size());
    bgObjects.push_back(&ground);
    bgObjects.push_back(&torch);
    for (auto& t : trees) { bgObjects.push_back(&t); }
    for (auto& c : cliffs) { bgObjects.push_back(&c); }
}

void Forest::createCliffs() {
    cliffs.reserve(3);

    // up
    BgObject cliffUp(
        "resources/cliff/cliff.obj",   // file path
        glm::vec3(0.0f, 0.0f, radius), // position
        glm::vec3(1.0f),               // scaling vector
        BoundingBox(                   // bounding box
            glm::vec3(-500.0f, 0.0f, 0.0f),
            glm::vec3(500.0f, 5.0f, 10.0f)
        )
    );
    cliffs.push_back(cliffUp);

    // left
    BgObject cliffLeft(
        cliffUp,
        BoundingBox(
            glm::vec3(20.0f, 0.0f, -500.0f),
            glm::vec3(30.0f, 5.0f, 500.0f)
        )
    );
    cliffs.push_back(cliffLeft);
    cliffs.back().getModel()
        .setPosition(glm::vec3(radius, 0.0f, 0.0f))
        .rotate(glm::radians(90.0f));

    // right
    BgObject cliffRight(
        cliffUp,
        BoundingBox(
            glm::vec3(-30.0f, 0.0f, -500.0f),
            glm::vec3(-20.0f, 5.0f, 500.0f)
        )
    );
    cliffs.push_back(cliffRight);
    cliffs.back().getModel()
        .setPosition(glm::vec3(-radius, 0.0f, 0.0f))
        .rotate(glm::radians(-90.0f));
}

/**
 * Generates n trees in a circle. The generated trees have a randomized scale
 * and rotation.
 */
void Forest::generateTrees(unsigned int nTrees) {
    std::uniform_real_distribution<float> dScale(1.0f, 1.5f);
    std::uniform_real_distribution<float> dRadius(0.0f, this->radius);
    std::uniform_real_distribution<float> dAngle(0, glm::two_pi<float>());

    trees.reserve(nTrees);

    Tree tree(
        glm::vec3(0.0f, 0.0f, 0.0f), // position
        glm::vec3(10.0f),            // scaling vector
        dAngle(randomGen)            // phase shift
    );

    auto generatedTrees = 0u;
    while (generatedTrees != nTrees) {
        auto radius = dRadius(randomGen);
        auto angle = dAngle(randomGen);
        glm::vec3 position(
            radius * cos(angle),
            0.0f,
            radius * sin(angle)
        );

        // discard trees generated in the river's path
        if (position.x >= -50.0f && position.x <= 35.0f) {
            continue;
        }

        trees.push_back(
            Tree(tree, dAngle(randomGen))
        );
        trees.back().getModel()
            .setPosition(position)
            .scale(glm::vec3(1.0f, dScale(randomGen), 1.0f))
            .rotate(dAngle(randomGen));

        generatedTrees++;
    }
}

void Forest::update() {
    for (auto& t : trees) { t.update(); }
}

std::vector<BgObject*>& Forest::getBgObjects() { return bgObjects; }
BgObject& Forest::getWaterfall() { return waterfall; }
BgObject& Forest::getRiver() { return river; }
BgObject& Forest::getFire() { return fire; }
