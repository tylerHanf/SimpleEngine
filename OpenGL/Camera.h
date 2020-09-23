#pragma once
#include <GLM/glm.hpp>

class Camera {
 public:
    Camera(glm::vec3 position);
    void ChangeLocation(glm::vec3 newPosition);
    glm::vec3 getPosition(void);
    void MoveForward(void);
    void MoveBack(void);
    void MoveRight(void);
    void MoveLeft(void);
    glm::vec3 GetLookAt(void);
    glm::vec3 GetUp(void);
    float getSpeed(void);
    void setSpeed(float newSpeed);
    void LookAround(double xpos, double ypos);

 private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float speed;

    float xpos, ypos;
    float lastX, lastY;
    float yaw, pitch;
    float sensitivity;
};
