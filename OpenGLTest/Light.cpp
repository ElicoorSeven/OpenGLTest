#include "Light.h"
#include <iostream>;
Light::Light()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	diffuseIntensity = 0.0f;
	shadowMap = 0;
}

Light::Light(GLfloat shadowWidth, GLfloat shadowHeight, 
	GLfloat red, GLfloat green, GLfloat blue, 
	GLfloat aIntensity, GLfloat dIntensity)
{

	shadowMap = new ShadowMap();
	shadowMap->Init(shadowWidth, shadowHeight);
	color = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
	diffuseIntensity = dIntensity;
}

void Light::UseLight(GLfloat ambientItensityLocation, GLfloat ambientColorLocation,
	GLfloat diffuseIntensityLocation, GLfloat directionLocation)
{
}

Light::~Light()
{
}
