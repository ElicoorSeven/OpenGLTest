#pragma once

#include <stdio.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class MyGLWindow
{
public:
	MyGLWindow();
	MyGLWindow(GLint windowWidth, GLint windowHeight);
	int Initialize();
	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }
	bool getShouldClose() {return !glfwWindowShouldClose(mainWindow);}
	void swapBuffers() {glfwSwapBuffers(mainWindow);}
	~MyGLWindow();

private:
	GLFWwindow* mainWindow;
	GLint bufferWidth;
	GLint bufferHeight;
	GLint windowWidth;
	GLint windowHeight;
};


