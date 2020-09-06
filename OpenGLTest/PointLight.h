#pragma once
#include "Light.h"
#include "OmniShadowMap.h"
#include <vector>
class PointLight : public Light
{
public:
	PointLight();
	PointLight(GLuint shadowWidth, GLuint shadowHeight, GLfloat near, GLfloat far,
		GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat attenuationConst, GLfloat attenuationLinear, GLfloat attenuationExponent);
	void UseLight(GLuint ambientItensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, GLuint positionLocation,
		GLuint attenuationConstantLocation, GLuint attenuationLinearLocation, GLuint attenuationExponentLocation);

	std::vector<glm::mat4> CalculateLightTransform();
	GLfloat GetFarPlane();
	glm::vec3 GetPosition();

	~PointLight();

protected:
	GLfloat attenuationConst, attenuationLinear, attenuationExponent;
	glm::vec3 position;
	GLfloat farPlane;
};

