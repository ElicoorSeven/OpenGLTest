// OpenGLTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "MyGLWindow.h"
#include "Mesh.h"
#include "Shader.h"

const float toRadians = 3.14152965f / 180.0f;

MyGLWindow mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

//vertex shader

static const char* vShader = "Shaders/shader.vert";

static const char* fShader = "Shaders/shader.frag";

void CreateShaders() {
    Shader *shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

void CreateObjects()
{

    unsigned int indices[] = { 
        0, 1, 2,
        1, 2, 3,
        2, 3, 0,
        0, 1, 3
    };

    GLfloat vertices[] = {
        -1.0f,-1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f,  0.0f,
        0.0f, -1.f, 1.0f,
    };

    Mesh* firstObject = new Mesh();
    firstObject->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(firstObject);

    Mesh* secondObject = new Mesh();
    secondObject->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(secondObject);
}

int main()
{
    mainWindow = MyGLWindow(800, 600);
    mainWindow.Initialize();
    CreateObjects();
    CreateShaders();

    GLuint uniformProjection = 0, uniformModel = 0;

    glm::mat4 projection = glm::perspective(40.0f, 
        (GLfloat)mainWindow.getBufferWidth()/(GLfloat)mainWindow.getBufferHeight(),
        0.1f, 
        100.0f);

    while (mainWindow.getShouldClose()) {
        glfwPollEvents();
        glClearColor(0.0f, 0.3f, 0.0f, .5f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();

        glm::mat4 model(1.0f);

        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshList[1]->RenderMesh();

        glUseProgram(0);

        mainWindow.swapBuffers();
    }
}