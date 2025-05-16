#include "EuclideCamera.h"

#include <iostream>

void EuclideCamera::setOrthographicProjection(float left, float right, float top, float bottom, float near, float far) {
    projectionMatrix = glm::mat4{ 1.0f };
    projectionMatrix[0][0] = 2.f / (right - left);
    projectionMatrix[1][1] = 2.f / (bottom - top);
    projectionMatrix[2][2] = 1.f / (far - near);
    projectionMatrix[3][0] = -(right + left) / (right - left);
    projectionMatrix[3][1] = -(bottom + top) / (bottom - top);
    projectionMatrix[3][2] = -near / (far - near);
}

void EuclideCamera::setPerspectiveProjection(float fovy, float aspect, float nearPlane, float farPlane) {
    fov = fovy;
    near = nearPlane;
    far = farPlane;
    aspectRatio = aspect;

    assert(glm::abs(aspect - std::numeric_limits<float>::epsilon()) > 0.0f);
    projectionMatrix = glm::perspective(fovy, aspect, nearPlane, farPlane);
    projectionMatrix[1][1] *= -1.0f; // Setting +Y axis to up
}

void EuclideCamera::updatePerpectiveProjection() {

    assert(glm::abs(aspectRatio - std::numeric_limits<float>::epsilon()) > 0.0f);
    projectionMatrix = glm::perspective(fov, aspectRatio, near, far);
    projectionMatrix[1][1] *= -1.0f; // Setting +Y axis to up
}

void EuclideCamera::updateAspectRatio(float aspect)
{
    aspectRatio = aspect;
    updatePerpectiveProjection();
}

void EuclideCamera::setViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up) {
    cameraPosition = position;
    targetPosition = target;

    glm::vec3 direction = glm::normalize(target - position);
    distanceToTarget = glm::length(target - position);

    orientation = glm::quatLookAt(direction, up);

    updateViewMatrix();
}

void EuclideCamera::orbit(float deltaYaw, float deltaPitch) {

    glm::vec3 yAxis{ 0.0, 1.0, 0.0 };
    glm::mat4 rotMat{ 1.f };

    rotMat = glm::rotate(rotMat, deltaYaw, yAxis);

    glm::vec3 rightAxis = glm::normalize(orientation * glm::vec3(1.0, 0.0, 0.0));
    glm::vec3 camUp = glm::normalize(orientation * glm::vec3(0.0, 1.0, 0.0));
    glm::vec3 targetDir = glm::normalize(orientation * glm::vec3(0.0, 0.0, 1.0));

    if (glm::dot(camUp, yAxis) < 0.1f) {
        if (targetDir.y < 0.0f && deltaPitch < 0.0f) {
            rotMat = glm::rotate(rotMat, deltaPitch, rightAxis);
        }
        else if (targetDir.y > 0.0f && deltaPitch > 0.0f) {
            rotMat = glm::rotate(rotMat, deltaPitch, rightAxis);
        }
    }
    else {
        rotMat = glm::rotate(rotMat, deltaPitch, rightAxis);
    }

    glm::vec3 localPosition = cameraPosition - targetPosition;
    localPosition = glm::vec3(rotMat * glm::vec4(localPosition, 1.0f));

    cameraPosition = targetPosition + localPosition;

    glm::vec3 direction = glm::normalize(targetPosition - cameraPosition);
    orientation = glm::quatLookAt(direction, glm::vec3(0.0, 1.0, 0.0));

    updateViewMatrix();
}

void EuclideCamera::dolly(float delta) {

    distanceToTarget = glm::max(0.1f, distanceToTarget + delta);

    glm::vec3 targetAxis = orientation * glm::vec3(0.f, 0.f, 1.0);
    cameraPosition = targetPosition + (targetAxis * distanceToTarget);

    updateViewMatrix();
}


void EuclideCamera::pan(glm::vec2 delta) {

    glm::vec3 upAxis = glm::normalize(orientation * glm::vec3(0.0, 1.0, 0.0));
    glm::vec3 rightAxis = glm::normalize(orientation * glm::vec3(1.0, 0.0, 0.0));

    glm::vec3 move = upAxis * delta.y;
    move += rightAxis * delta.x;

    cameraPosition += move;
    targetPosition += move;

    updateViewMatrix();
}



void EuclideCamera::updateViewMatrix() {
    viewMatrix = glm::lookAt(cameraPosition, targetPosition, orientation * glm::vec3(0.f, 1.f, 0.f));
}
