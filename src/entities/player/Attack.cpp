#include "inputs/Inputs.hpp"
#include "entities/player/Attack.hpp"
#include "tools/LocalBasis.hpp"

Attack::Attack(Player& player) :
    Entity("attack"),
    player(player),
    magicCircle1("resources/attack/circle1.obj"),
    magicCircle2(magicCircle1),
    magicCircle3(magicCircle1),
    magicTriangle("resources/attack/triangle.obj"),
    orb("resources/attack/orb.obj"),
    laser("resources/attack/laser.obj")
{
    magicCircle1.translate(glm::vec3(0.0f, 0.3f, 0.0f))
                .scale(glm::vec3(0.5f));
    magicTriangle.translate(glm::vec3(0.0f, 0.3f, 0.0f));
    magicCircle2.translate(glm::vec3(0.0f, 4.0f, 2.5f))
                .scale(glm::vec3(0.25f))
                .rotate(glm::radians(90.0f), LocalBasis::z)
                .rotate(glm::radians(90.0f), LocalBasis::x);
    magicCircle3.translate(glm::vec3(0.0f, 5.0f, 0.0f))
                .scale(glm::vec3(0.7f));
    orb.translate(magicCircle2.getPosition());
    laser.translate(magicCircle2.getPosition())
         .scale(glm::vec3(1.0f, 0.5f, 0.5f));

    Inputs::instance().addKeyHandler(eventHandler);
}

void Attack::update() {
    // transform magic circles
    glm::mat4 transformationCircle(1.0f);
    transformationCircle = glm::rotate(
        transformationCircle, (float) glfwGetTime(), LocalBasis::y
    );
    magicCircle2.setTransformation(transformationCircle);

    transformationCircle = glm::scale(
        transformationCircle,
        glm::vec3((float) exp(sin(glfwGetTime())))
    );
    magicCircle1.setTransformation(transformationCircle);

    transformationCircle = glm::mat4(1.0f);
    transformationCircle = glm::rotate(
        transformationCircle, (float) glfwGetTime(), LocalBasis::z
    );
    magicCircle3.setTransformation(transformationCircle);

    // transform magic triangle
    glm::mat4 transformationTriangle(1.0f);
    transformationTriangle = glm::rotate(
        transformationTriangle, -0.5f * (float) glfwGetTime(), LocalBasis::y
    );
    magicTriangle.setTransformation(transformationTriangle);

    // transform orb
    glm::mat4 transformationOrb(1.0f);
    transformationOrb = glm::scale(
        transformationOrb,
        glm::vec3((float) 0.5 * (sin(4 * glfwGetTime())) + 1.0)
    );
    orb.setTransformation(transformationOrb);
}

/**
 * Returns the model's modelMatrix multiplied by the player's modelMatrix in
 * order for this model to follow the player.
 */
glm::mat4 Attack::getModelMatrix(Model& model) {
    return player.getModel().getModelMatrix() * model.getModelMatrix();
}

Model& Attack::getMagicCircle1() { return magicCircle1; }
Model& Attack::getMagicCircle2() { return magicCircle2; }
Model& Attack::getMagicCircle3() { return magicCircle3; }
Model& Attack::getMagicTriangle() { return magicTriangle; }
Model& Attack::getOrb() { return orb; }
Model& Attack::getLaser() { return laser; }

bool Attack::isAttacking() { return eventHandler.isAttacking(); }
bool Attack::isLoading() { return eventHandler.isLoading(); }
