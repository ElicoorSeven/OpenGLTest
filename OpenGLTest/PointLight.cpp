#include "PointLight.h"

PointLight::PointLight() : Light()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	attenuationConst = 0;
	attenuationLinear = 0;
	attenuationExponent = 0;
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, 
	GLfloat xPos, GLfloat yPos, GLfloat zPos, 
	GLfloat attenuationConst, GLfloat attenuationLinear, GLfloat attenuationExponent)
	: Light(1024, 1024, red, green, blue, aIntensity, dIntensity)
{
	position = glm::vec3(red, green, blue);
	this->attenuationConst = attenuationConst;
	this->attenuationLinear = attenuationLinear;
	this->attenuationExponent = attenuationExponent;
}

void PointLight::UseLight(GLuint ambientItensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation,
	GLuint positionLocation, GLuint attenuationConstantLocation, GLuint attenuationLinearLocation, GLuint attenuationExponentLocation)
{
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientItensityLocation, ambientIntensity);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);

	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(attenuationConstantLocation, attenuationConst);
	glUniform1f(attenuationLinearLocation, attenuationLinear);
	glUniform1f(attenuationExponentLocation, attenuationExponent);
}

PointLight::~PointLight()
{
}
