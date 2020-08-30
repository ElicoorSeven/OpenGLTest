#pragma once

#include <GL\glew.h>

class Material
{
public:
	Material();
	Material(GLfloat sIntensity, GLfloat sPower);
	~Material();
	void UseMaterial(GLuint specularIntensityLocation, GLuint specularPowerLocation);
private:
	GLfloat specularIntensity;
	GLfloat specularPower;
};

