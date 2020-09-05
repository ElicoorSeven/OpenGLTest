#pragma once
#include "GL/glew.h"
#include <iostream>

class ShadowMap
{
public:
	ShadowMap();
	virtual bool Init(GLuint width, GLuint height);
	virtual void Write();
	virtual void Read(GLenum textureUnit);
	GLuint GetShadowWidth();
	GLuint GetShadowHeight();
	~ShadowMap();
protected:
	GLuint FBO, shadowMap;
	GLuint shadowWidth, shadowHeight;
};

