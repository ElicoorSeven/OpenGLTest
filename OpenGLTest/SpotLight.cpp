#include "SpotLight.h"

SpotLight::SpotLight() : PointLight()
{
	edge = 0;
	procEdge = 0;
	direction = glm::vec3(0.0f, -1.0f, 0);
}

SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, 
	GLfloat xPos, GLfloat yPos, GLfloat zPos,
	GLfloat xDir, GLfloat yDir, GLfloat zDir, 
	GLfloat attenuationConst, GLfloat attenuationLinear, GLfloat attenuationExponent, GLfloat edge) : PointLight(red, green, blue, aIntensity, dIntensity, 
		xPos, yPos, zPos, attenuationConst, attenuationLinear, attenuationExponent)
{
	direction = normalize(glm::vec3(xDir, yDir, zDir));
	this->edge = edge;
	procEdge = cosf(glm::radians(edge));
}

void SpotLight::UseLight(GLuint ambientItensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, 
	GLuint positionLocation, GLuint attenuationConstantLocation, GLuint attenuationLinearLocation, 
	GLuint attenuationExponentLocation, GLuint directionLocation, GLuint edgeLocation)
{
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientItensityLocation, ambientIntensity);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);

	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(attenuationConstantLocation, attenuationConst);
	glUniform1f(attenuationLinearLocation, attenuationLinear);
	glUniform1f(attenuationExponentLocation, attenuationExponent);
	
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(edgeLocation, procEdge);
}

SpotLight::~SpotLight()
{
}
