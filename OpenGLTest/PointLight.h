#pragma once
#include "Light.h"
class PointLight : public Light
{
public:
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat attenuationConst, GLfloat attenuationLinear, GLfloat attenuationExponent);
	void UseLight(GLuint ambientItensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, GLuint positionLocation,
		GLuint attenuationConstantLocation, GLuint attenuationLinearLocation, GLuint attenuationExponentLocation);
	~PointLight();

protected:
	GLfloat attenuationConst, attenuationLinear, attenuationExponent;
	glm::vec3 position;
};

