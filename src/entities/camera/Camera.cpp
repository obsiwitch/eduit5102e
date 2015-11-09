#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <cmath>

#include "tools/LocalBasis.hpp"
#include "entities/camera/Camera.hpp"

/**
 * Creates a perspective Camera which holds the view & projection matrices. In
 * order to create these matrices, we need the following parameters.
 * @param position Position of the camera.
 * @param direction direction towards the camera's target (reversed, will be
 * normalized).
 * @param fov Fielf of view (radians).
 * @param width Used to compute the aspect ratio (width/height).
 * @param height Used to compute the aspect ratio (width/height).
 * @param zNear Distance from the camera to the near clipping plane.
 * @param zFar Distance from the camera to the far clipping plane.
 */
Camera::Camera(
    const glm::vec3& position, const glm::vec3& direction,
    float fov, float width, float height, float zNear, float zFar
) :
    Entity("camera", position),
    cameraMouseHandler(this)
{
    this->direction = glm::normalize(direction);
    
    this->fov = fov;
    this->width = width;
    this->height = height;
    this->zNear = zNear;
    this->zFar = zFar;
}

void Camera::translate(const glm::vec3& vec) {
    position += vec;
}

void Camera::rotate(float angle, const glm::vec3& axis) {
    position = glm::rotate(position, angle, axis);
    direction = glm::normalize(glm::rotate(direction, angle, axis));
}

void Camera::rotate(const glm::vec2& delta) {
    rotate(glm::radians(delta.x), getUp()); // yaw
    
    float pitch = glm::degrees(std::asin(direction.y)) + delta.y;
    if (pitch > -80.0f && pitch < 80.0f) {
        rotate(glm::radians(delta.y), getRight());
    }
}

void Camera::zoom(float value) {
    position += direction * value;
}

void Camera::update(Shader& shader) {
    shader.setUniform("view", getViewMatrix());
    shader.setUniform("projection", getProjectionMatrix());
    shader.setUniform("cameraPosition", position);
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(
        position,
        position + direction,
        getUp()
    );
}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::perspectiveFov(fov, width, height, zNear, zFar);
}

glm::vec3 Camera::getRight() {
    return glm::normalize(glm::cross(direction, LocalBasis::y));
}

glm::vec3 Camera::getUp() {
    return glm::normalize(glm::cross(getRight(), direction));
}

float Camera::getWidth() { return width; }
float Camera::getHeight() { return height; }

MouseHandler& Camera::getMouseHandler() {
    return cameraMouseHandler;
}
