#include "Camera.h"
#include <GLFW/glfw3.h>

Camera::Camera(glm::vec3 _position, glm::vec3 _target, glm::vec3 worldup)
{
    Position = _position;
    WorldUp = worldup;
    Forward = glm::normalize(_target - _position);
    Right = glm::normalize(glm::cross(Forward, WorldUp)); // Normalize Right vector
    Up = glm::normalize(glm::cross(Right, Forward)); // Ensure orthogonality
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
{
    this->yaw = yaw;
    this->pitch = pitch;
    Position = position;
    WorldUp = worldup;
    Forward.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    Forward.y = sin(glm::radians(pitch));
    Forward.z = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    Forward = glm::normalize(Forward); // Normalize Forward vector
    Right = glm::normalize(glm::cross(Forward, WorldUp)); // Normalize Right vector
    Up = glm::normalize(glm::cross(Right, Forward)); // Ensure orthogonality
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY)
{
    float sensitivity = 0.05;
    deltaX *= sensitivity;
    deltaY*= sensitivity;
    yaw += deltaX;
    pitch += deltaY;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    Forward.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    Forward.y = sin(glm::radians(pitch));
    Forward.z = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    Right = glm::normalize(glm::cross(Forward, WorldUp)); // Normalize Right vector
    Up = glm::normalize(glm::cross(Right, Forward)); // Ensure orthogonality
}

void Camera::UpdateCameraPos()
{
    float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    glm::mat4 view;
    view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Forward, Up);
}
