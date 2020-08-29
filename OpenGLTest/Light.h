#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
		GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);
	void UseLight(GLfloat ambientItensity, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);
	~Light();
private:
	glm::vec3 color;
	glm::vec3 direction;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
};

