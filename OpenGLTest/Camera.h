#pragma once

#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <GLFW\glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 originalPosition, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat turnSpeed, GLfloat movementSpeed);
	~Camera();
	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);
	glm::mat4 calculateViewMatrix();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;
	
	GLfloat movementSpeed;
	GLfloat turnSpeed;
	
	//TODO: implement roll
	void update();

};

