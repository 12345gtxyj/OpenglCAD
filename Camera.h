#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;
class Camera
{
public:
	Camera(glm::vec3 _position, glm::vec3 _target, glm::vec3 worldup);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);
	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	float speedZ;
	float yaw;
	float pitch;
	void ProcessMouseMovement(float deltaX,float deltaY);
	void UpdateCameraPos();
	glm::mat4 GetViewMatrix();
};