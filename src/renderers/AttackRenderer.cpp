#include "AttackRenderer.hpp"

AttackRenderer::AttackRenderer(
    Attack& attack, Camera& camera,
    std::vector<std::shared_ptr<Entity>>& lights
) :
    attack(attack), camera(camera), lights(lights)
{
    shader.add(GL_VERTEX_SHADER, "src/shaders/main/main.vs")
          .add(GL_FRAGMENT_SHADER, "src/shaders/main/main.fs")
          .add(GL_FRAGMENT_SHADER, "src/shaders/textures/texture.fs")
          .add(GL_FRAGMENT_SHADER, "src/shaders/main/phong.fs")
          .add(GL_FRAGMENT_SHADER, "src/shaders/main/lights.fs")
          .link();
}
    
void AttackRenderer::render() {
    shader.use();
    for (auto l : lights) { l->update(shader); }
    
    shader.setUniform("view", camera.getViewMatrix());
    shader.setUniform("projection", camera.getProjectionMatrix());
    shader.setUniform("cameraPosition", camera.getPosition());
    
    render(attack.getMagicCircle1());
    render(attack.getMagicCircle2());
    render(attack.getMagicTriangle());
}

void AttackRenderer::render(Model& model) {
    shader.setUniform("model", model.getModelMatrix());
    shader.setUniform("normalMatrix", model.getNormalMatrix());
    model.draw(shader);
}