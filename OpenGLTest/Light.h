#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity);
	virtual void UseLight(GLfloat ambientItensity, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);
	~Light();

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
};

