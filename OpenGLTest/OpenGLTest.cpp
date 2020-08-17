// OpenGLTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14152965f / 180.0f;

GLuint VAO, VBO, shader, uniformModel;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncriment = 0.001f;

float curAngle = 0.0f;

bool sizeDirection = true;
float curSize = 0.5f;
float maxSize = 1.0f;
float minSize = 0.0f;

//vertex shader

static const char* vShader = "                             \n\
#version 330                                               \n\
layout(location = 0) in vec3 pos;                          \n\
uniform mat4 model;                                        \n\
out vec4 vertexColor;                                       \n\
void main()                                                \n\
{                                                          \n\
    gl_Position = model * vec4(pos, 1);    \n\
    vertexColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);      \n\
}";

static const char* fShader = "                             \n\
#version 330                                               \n\
out vec4 color;                                            \n\
in vec4 vertexColor;                                              \n\
void main()                                                \n\
{                                                          \n\
    color = vertexColor;              \n\
}";

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {

    GLuint theShader = glCreateShader(shaderType);
    
    const GLchar* theCode[1];
    theCode[0] = shaderCode;
    
    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);
    
    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(theShader, sizeof(eLog), NULL, eLog);
        printf("Error compiling the %d shader: %s \n", shaderType, eLog);
        return;
    }
    glAttachShader(theProgram, theShader);
}

void CompileShaders() {
    shader = glCreateProgram();
    if (!shader) {
        printf("Error creating shaders!");
        return;
    }

    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);
    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error linking program: %s \n", eLog);
        return;
    }

    uniformModel = glGetUniformLocation(shader, "model");

}

void CreateTriangle()
{
    GLfloat vertices[] = {
        -1.0f,-1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f,  0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

int main()
{
    if (!glfwInit()) {
        printf("GLFW Failed to Initialize!");
        glfwTerminate();
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // no backwards compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // allow forwards compatibility

    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
    if (!mainWindow) {
        printf("MainWindow failed to Initialize!");
        glfwTerminate();
        return 1;
    }

    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    glfwMakeContextCurrent(mainWindow);

    glewExperimental = GL_TRUE; // allow modern features
    if (glewInit() != GLEW_OK) {
        printf("GLEW failed to Initialize!");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }
    glViewport(0, 0, bufferWidth, bufferHeight); // set viewport size

    CreateTriangle();
    CompileShaders();

    while (!glfwWindowShouldClose(mainWindow)) {
        glfwPollEvents();

        if (direction) {
            triOffset += triIncriment;
        }
        else {
            triOffset -= triIncriment;
        }

        if (abs(triOffset) >= triMaxOffset) {
            direction = !direction;
        }

        if (sizeDirection) {
            curSize += 0.001f;

        }
        else {
            curSize -= 0.001f;
        }

        if (curSize >= maxSize || curSize <= minSize) sizeDirection = !sizeDirection;


        curAngle += 0.001f;

        glClearColor(0.0f, 1.0f, 0.0f, .5f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shader);

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
        model = glm::rotate(model, curAngle, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(curSize, curSize * -1, .6f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(0);

        glfwSwapBuffers(mainWindow);
    }
}