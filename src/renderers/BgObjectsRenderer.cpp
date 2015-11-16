#include "BgObjectsRenderer.hpp"

BgObjectsRenderer::BgObjectsRenderer(
    std::vector<BgObject>& bgObjects, Camera& camera,
    std::vector<std::shared_ptr<Entity>>& lights
) :
    bgObjects(bgObjects), camera(camera)
{
    shader.add(GL_VERTEX_SHADER, "src/shaders/main/main.vs")
          .add(GL_FRAGMENT_SHADER, "src/shaders/main/main.fs")
          .add(GL_FRAGMENT_SHADER, "src/shaders/main/toon.fs")
          .add(GL_FRAGMENT_SHADER, "src/shaders/main/lights.fs")
          .link();
    
    shader.use();
    for (auto l : lights) { l->update(shader); }
}
    
void BgObjectsRenderer::render() {
    shader.use();
    shader.setUniform("time", (float) glfwGetTime());
    
    shader.setUniform("view", camera.getViewMatrix());
    shader.setUniform("projection", camera.getProjectionMatrix());
    shader.setUniform("cameraPosition", camera.getPosition());
    
    for (auto o : bgObjects) {
        shader.setUniform("model", o.getModel().getModelMatrix());
        shader.setUniform("normalMatrix", o.getModel().getNormalMatrix());
        shader.setUniform("setSilhouette", o.getSilhouette());
        shader.setUniform("breathing", false);
        
        o.getModel().draw(shader);
    }
}