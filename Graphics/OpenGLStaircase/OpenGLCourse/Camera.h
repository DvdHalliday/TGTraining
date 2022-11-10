#pragma	once

#include <GL/glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <GLFW/glfw3.h>

class FCamera
{
private:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	GLfloat Yaw;
	GLfloat Pitch;

	GLfloat MovementSpeed;
	GLfloat TurnSpeed;

	void Update();

public:
	FCamera(glm::vec3 NewPosition, glm::vec3 NewWorldUp, GLfloat NewYaw, GLfloat NewPitch, GLfloat NewMovementSpeed, GLfloat NewTurnSpeed);
	FCamera() {}
	~FCamera() = default;

	void KeyControl(bool* Keys, GLfloat DeltaTime);
	void MouseControl(GLfloat XChange, GLfloat YChange);

	glm::mat4 CalculateViewMatrix();
};