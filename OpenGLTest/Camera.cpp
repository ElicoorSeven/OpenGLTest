#include "Camera.h"

Camera::Camera()
{
	position = glm::vec3(0, 0, 0);
	worldUp = glm::vec3(0, 0, 0);
	yaw = 0;
	pitch = 0;
	turnSpeed = 0;
	movementSpeed = 0;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	right = glm::vec3(0, 0, 0);
	up = glm::vec3(0, 0, 0);
}

Camera::Camera(glm::vec3 originalPosition, glm::vec3 startUp, GLfloat yaw, GLfloat pitch, GLfloat turnSpeed, GLfloat movementSpeed)
{
	position = originalPosition;
	this->worldUp = startUp;
	this->yaw = yaw;
	this->pitch = pitch;
	this->turnSpeed = turnSpeed;
	this->movementSpeed = movementSpeed;
	front = glm::vec3(0.0f,0.0f,-1.0f);
	right = glm::vec3(0, 0, 0);
	up = glm::vec3(0, 0, 0);

	update();

}

Camera::~Camera()
{
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{ 
	GLfloat velocity = movementSpeed * deltaTime;
	if (keys[GLFW_KEY_W]) {
		position += front * velocity;
	}
	if (keys[GLFW_KEY_S]) {
		position -= front * velocity;
	}
	if (keys[GLFW_KEY_A]) {
		position -= right * velocity;
	}
	if (keys[GLFW_KEY_D]) {
		position += right * velocity;
	}
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;
	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}
	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw) * cos(glm::radians(pitch)));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw) * cos(glm::radians(pitch)));
	front = glm::normalize(front);
	
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}
