#pragma once
#include "Mesh.h"
#include "Shader.h"
class Skybox
{
public:
	Skybox();
	Skybox(std::vector<std::string> faceLocations);
	void Draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	~Skybox();

private:
	Mesh* skyMesh;
	Shader* skyShader;
	GLuint textureID;
	GLuint uniformProjection, uniformView;
};

