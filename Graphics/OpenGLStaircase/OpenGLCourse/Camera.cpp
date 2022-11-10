#include "Camera.h"

void FCamera::Update()
{
	Front.x = cosf(glm::radians(Yaw) * cosf(glm::radians(Pitch)));
	Front.y = sinf(glm::radians(Pitch));
	Front.z = sinf(glm::radians(Yaw) * cosf(glm::radians(Pitch)));
	Front = glm::normalize(Front);

	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}

FCamera::FCamera(glm::vec3 NewPosition, glm::vec3 NewWorldUp, GLfloat NewYaw, GLfloat NewPitch, GLfloat NewMovementSpeed, GLfloat NewTurnSpeed) :
	Position(NewPosition),
	WorldUp(NewWorldUp),
	Yaw(NewYaw),
	Pitch(NewPitch),
	Front(glm::vec3(0.f, 0.f, -1.f)),
	MovementSpeed(NewMovementSpeed),
	TurnSpeed(NewTurnSpeed)
{
	Update();
}

void FCamera::KeyControl(bool* Keys, GLfloat DeltaTime)
{
	GLfloat Velocity = MovementSpeed * DeltaTime;
	if (Keys[GLFW_KEY_W])
	{
		Position += Front * Velocity;
	}

	if (Keys[GLFW_KEY_D])
	{
		Position += Right * Velocity;
	}

	if (Keys[GLFW_KEY_S])
	{
		Position -= Front * Velocity;
	}

	if (Keys[GLFW_KEY_A])
	{
		Position -= Right * Velocity;
	}

	if (Keys[GLFW_KEY_Q])
	{
		Position -= WorldUp * Velocity;
	}

	if (Keys[GLFW_KEY_E])
	{
		Position += WorldUp * Velocity;
	}
}

void FCamera::MouseControl(GLfloat XChange, GLfloat YChange)
{
	XChange *= TurnSpeed;
	YChange *= TurnSpeed;

	Yaw += XChange;
	Pitch += YChange;

	if(Pitch > 89.f)
	{
		Pitch = 89.f;
	}

	if (Pitch < -89.f)
	{
		Pitch = -89.f;
	}

	Update();
}

glm::mat4 FCamera::CalculateViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}
