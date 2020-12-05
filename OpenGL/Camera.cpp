#include "Camera.h"

Camera::Camera(glm::vec3 inPosition) {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    speed = 5.0;
    xpos, ypos = 400;
    lastX, lastY = 400;
    sensitivity = 0.1f;
    yaw = -90.0f;
    pitch = 0;
}

Camera::Camera(glm::vec3 inPosition, float inSpeed) {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    speed = inSpeed;
    xpos, ypos = 0;
    lastX, lastY = 0;
    sensitivity = 0.1f;
    yaw = -90.0f;
    pitch = 0;  
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

void Camera::LookAround(double xpos, double ypos) {
    float xoffset = xpos - lastX;
    float yoffset = ypos - lastY;

    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
	pitch = 89.0f;
    if (pitch < -89.0f)
	pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(-pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);
}
