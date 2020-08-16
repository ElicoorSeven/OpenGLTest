// OpenGLTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader, uniformXMove;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncriment = 0.001f;

//vertex shader

static const char* vShader = "                             \n\
#version 330                                               \n\
layout(location = 0) in vec3 pos;                          \n\
uniform float xMove;                                       \n\
void main()                                                \n\
{                                                          \n\
    gl_Position = vec4(.6 * pos.x + xMove, .6 * pos.y,pos.z,1);    \n\
}";

static const char* fShader = "                             \n\
#version 330                                               \n\
out vec4 color;                                            \n\
void main()                                                \n\
{                                                          \n\
    color = vec4(0.0,0.0,1.0,1);               \n\
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

    uniformXMove = glGetUniformLocation(shader, "xMove");

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW);
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

        glClearColor(0.0f, 1.0f, 0.0f, .5f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shader);
        glUniform1f(uniformXMove, triOffset);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(0);

        glfwSwapBuffers(mainWindow);
    }
}