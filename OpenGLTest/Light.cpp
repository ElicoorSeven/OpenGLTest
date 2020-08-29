#include "Light.h"

Light::Light()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity)
{
	color = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
}


//TODO Make this code not be as silly, so that people can't fuck up.
void Light::UseLight(GLfloat ambientItensityLocation, GLfloat ambientColorLocation)
{
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientItensityLocation, ambientIntensity);
}
 

Light::~Light()
{
}
