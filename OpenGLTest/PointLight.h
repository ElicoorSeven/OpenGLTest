#pragma once
#include "Light.h"
class PointLight : public Light
{
public:
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat attenuationConst, GLfloat attenuationLinear, GLfloat attenuationExponent);
	void UseLight(GLfloat ambientItensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, GLfloat positionLocation,
		GLfloat attenuationConstantLocation, GLfloat attenuationLinearLocation, GLfloat attenuationExponentLocation);
	~PointLight();
private:
	glm::vec3 position;
	GLfloat attenuationConst, attenuationLinear, attenuationExponent;
};

