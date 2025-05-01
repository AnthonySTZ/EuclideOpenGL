#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>


class EuclideCamera {

public:
    // Projection settings
    void setOrthographicProjection(float left, float right, float top, float bottom, float near, float far);
    void setPerspectiveProjection(float fovy, float aspect, float near, float far);

    void updatePerpectiveProjection();
    void updateAspectRatio(float aspect);

    // View controls
    void setViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up = glm::vec3{ .0f, 1.f, .0f });

    // Orientation
    void orbit(float deltaYaw, float deltaPitch);
    void dolly(float delta);
    void pan(glm::vec2 delta);

    // View and projection matrices
    const glm::mat4& getProjection() const { return projectionMatrix; };
    const glm::mat4& getView() const { return viewMatrix; };

    // Getters for position and target
    glm::vec3 getTarget() const { return targetPosition; };
    glm::vec3 getPosition() const { return cameraPosition; };

private:
    void updateViewMatrix();

    glm::mat4 projectionMatrix{ 1.f };
    glm::mat4 viewMatrix{ 1.f };

    glm::vec3 cameraPosition{ 0.f };
    glm::vec3 targetPosition{ 0.f };
    glm::quat orientation = glm::quat(glm::vec3(0.f)); // Camera orientation as a quaternion

    float distanceToTarget = 10.f;
    float fov, near, far, aspectRatio;

};