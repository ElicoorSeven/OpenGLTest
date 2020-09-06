#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>
#include "glm/ext.hpp"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "CommonValues.h"
#include "SpotLight.h"

class Shader
{

public:
	Shader();
	~Shader();

	void CreateFromString(const char *vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
	void CreateFromFiles(const char* vertexLocation, const char* geometryLocation, const char* fragmentLocation);
	void Validate();
	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColorLocation();
	GLuint GetDiffuseIntensityLocation();
	GLuint GetDirectionLocation();
	GLuint GetSpecularIntensityLocation();
	GLuint GetSpecularPowerLocation();
	GLuint GetEyePositionLocation();
	GLuint GetOmniLightPositionLocation();
	GLuint GetFarPlaneLocation();

	void UseShader();
	void ClearShader();
	void SetDirectionalLight(DirectionalLight* dLight);
	void SetPointLights(PointLight* pLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);
	void SetSpotLights(SpotLight* sLight, unsigned int lightCount, unsigned int textureUnit, unsigned int offset);
	void SetTexture(GLuint textureUnit);
	void SetDirectionalShadowMap(GLuint textureUnit);
	void SetDirectionalLightTransform(glm::mat4* lTransform);
	void SetOmniLightMatrices(std::vector<glm::mat4> lMatrices);

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView,
		uniformSpecularIntensity, uniformSpecularPower, uniformEyePosition,uniformTexture,
		uniformDirectionalLightTransform, uniformDirectionalShadowMap,
		uniformPointLightCount, uniformSpotlightCount,
		uniformOmniLightPos, uniformFarPlane;

	GLuint uniformLightMatrices[6];

	struct {
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformDirection;
	} uniformDirectionalLight;

	struct {
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformAttenuationConstant;
		GLuint uniformAttenuationLinear;
		GLuint uniformAttenuationExponent;
	} uniformPointLight[MAX_POINT_LIGHTS];

	struct {
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformAttenuationConstant;
		GLuint uniformAttenuationLinear;
		GLuint uniformAttenuationExponent;

		GLuint uniformDirection;
		GLuint uniformEdge;
	} uniformSpotLight[MAX_SPOT_LIGHTS];

	struct {
		GLuint uniformShadowMap;
		GLuint uniformFarPlane;
	} uniformOmniShadowMap[MAX_POINT_LIGHTS + MAX_SPOT_LIGHTS];

	void CompileShader(const char *vertexCode, const char* fragmentCode);
	void CompileShader(const char* vertexCode, const char* geometryCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	void CompileProgram();

};

