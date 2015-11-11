#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include "entities/Entity.hpp"
#include "entities/camera/CameraMouseHandler.hpp"

class Camera : public Entity {
public:
    Camera(
        const glm::vec3& position, const glm::vec3& target,
        const glm::vec3& targetOffset,
        float fov, float width, float height, float zNear, float zFar
    );
    
    void translate(const glm::vec3& vec);
    void rotate(float angle, const glm::vec3& axis);
    void rotate(const glm::vec2& delta);
    void zoom(float value);
    
    void update(Shader& shader, const glm::vec3& newTarget);
    void update(Shader& shader) override;
    
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    glm::vec3 getDirection();
    glm::vec3 getRight();
    glm::vec3 getUp();
    float getWidth();
    float getHeight();
    MouseHandler& getMouseHandler();
    
private:
    static const float MIN_PITCH;
    static const float MAX_PITCH;
    static const float MIN_ZOOM;
    static const float MAX_ZOOM;
    
    // View
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 targetOffset;
    CameraMouseHandler cameraMouseHandler;
    
    // Projection
    float fov;
    float width;
    float height;
    float zNear;
    float zFar;
};

#endif // CAMERA_HPP
