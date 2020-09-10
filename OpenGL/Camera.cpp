#include "Camera.h"

Camera::Camera(glm::vec3 inPosition) {
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    speed = 1.5;
}

void Camera::ChangeLocation(glm::vec3 newPosition) {
    position = newPosition;
}

void Camera::MoveForward(void) {
    position += speed * front;
}

void Camera::MoveBack(void) {
    position -= speed * front;
}

void Camera::MoveRight(void) {
    position += glm::normalize(glm::cross(front, up)) * speed;
}

void Camera::MoveLeft(void) {
    position -= glm::normalize(glm::cross(front, up)) * speed;
}

glm::vec3 Camera::GetLookAt(void) {
    return position + front;
}

glm::vec3 Camera::GetUp(void) {
    return up;
}

glm::vec3 Camera::getPosition(void) {
    return position;
}

float Camera::getSpeed(void) {
    return speed;
}

void Camera::setSpeed(float newSpeed) {
    speed = newSpeed;
}
