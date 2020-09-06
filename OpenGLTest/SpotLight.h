#pragma once
#include "PointLight.h"
class SpotLight :
    public PointLight
{
public:
    SpotLight();

    SpotLight(GLfloat shadowWidth, GLfloat shadowHeight,
        GLfloat near, GLfloat far, 
        GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
        GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat xDir, GLfloat yDir, GLfloat zDir,
        GLfloat attenuationConst, GLfloat attenuationLinear, GLfloat attenuationExponent, GLfloat edge);
    void UseLight(GLuint ambientItensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, GLuint positionLocation,
        GLuint attenuationConstantLocation, GLuint attenuationLinearLocation, GLuint attenuationExponentLocation,
        GLuint directionLocation, GLuint edgeLocation);

    ~SpotLight();
private:
    glm::vec3 direction;
    GLfloat edge, procEdge;

};

