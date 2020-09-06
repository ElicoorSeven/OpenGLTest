#include "PointLight.h"
#include <glm\ext\matrix_clip_space.hpp>
#include <glm\ext\matrix_transform.hpp>

PointLight::PointLight() : Light()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	attenuationConst = 0;
	attenuationLinear = 0;
	attenuationExponent = 0;
	farPlane = 0;
}

PointLight::PointLight(GLuint shadowWidth, GLuint shadowHeight, GLfloat near, GLfloat far,
	GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, 
	GLfloat xPos, GLfloat yPos, GLfloat zPos, 
	GLfloat attenuationConst, GLfloat attenuationLinear, GLfloat attenuationExponent)
	: Light(shadowWidth, shadowHeight, red, green, blue, aIntensity, dIntensity)
{
	shadowMap = new OmniShadowMap();
	shadowMap->Init(shadowWidth, shadowHeight);
	position = glm::vec3(xPos, yPos, zPos);
	this->attenuationConst = attenuationConst;
	this->attenuationLinear = attenuationLinear;
	this->attenuationExponent = attenuationExponent;
	farPlane = far;
	float aspect = (float) shadowWidth / (float) shadowHeight;
	lightProj = glm::perspective(glm::radians(90.0f), aspect, near, far);

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

std::vector<glm::mat4> PointLight::CalculateLightTransform()
{
	std::vector<glm::mat4> lightTransforms;
	lightTransforms.push_back(lightProj *
		glm::lookAt(position, position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	lightTransforms.push_back(lightProj *
		glm::lookAt(position, position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	lightTransforms.push_back(lightProj *
		glm::lookAt(position, position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
	lightTransforms.push_back(lightProj *
		glm::lookAt(position, position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
	lightTransforms.push_back(lightProj *
		glm::lookAt(position, position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
	lightTransforms.push_back(lightProj *
		glm::lookAt(position, position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

	return lightTransforms;
}

GLfloat PointLight::GetFarPlane()
{
	return farPlane;
}

glm::vec3 PointLight::GetPosition()
{
	return position;
}

PointLight::~PointLight()
{
}
