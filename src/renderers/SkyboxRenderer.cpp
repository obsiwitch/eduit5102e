#include <glm/gtc/matrix_transform.hpp>

#include "SkyboxRenderer.hpp"

SkyboxRenderer::SkyboxRenderer(Skybox& skybox, Camera& camera) :
    skybox(skybox), camera(camera)
{
    shader.add(GL_VERTEX_SHADER, "src/shaders/skybox/skybox.vs")
          .add(GL_FRAGMENT_SHADER, "src/shaders/skybox/skybox.fs")
          .link();
}

/**
 * Renders the skybox.
 * @note The depth function is changed from LESS to LEQUAL so that the skybox
 * passes the depth test. The depth buffer will be filled with the maximum
 * value (1.0) for the skybox.
 */
void SkyboxRenderer::render() {
    shader.use();
    
    shader.setUniform("view", camera.getNonTranslatedViewMatrix());
    shader.setUniform("projection", camera.getProjectionMatrix());
    shader.setUniform("cameraPosition", camera.getPosition());
    
    shader.setUniform("skybox", (GLuint) 0);
    shader.setUniform("rotationMatrix", glm::rotate(
        glm::mat4(),                   // matrix
        0.01f * (float) glfwGetTime(), // angle
        glm::vec3(0.0f, 1.0f, 0.0f)    // axis
    ));
    
    glDepthFunc(GL_LEQUAL);
    skybox.getTexture().bind();
    skybox.getModel().draw(shader);
    skybox.getTexture().unbind();
    glDepthFunc(GL_LESS);
}
