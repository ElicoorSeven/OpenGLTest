#pragma once

#include <stdio.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class MyGLWindow
{
public:
	// TODO: Factor Out Camera into its own class
	MyGLWindow();
	MyGLWindow(GLint windowWidth, GLint windowHeight);
	int Initialize();
	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }
	bool* getKeys();
	GLfloat getXChange();
	GLfloat getYChange();
	bool getShouldClose() {return !glfwWindowShouldClose(mainWindow);}
	void swapBuffers() {glfwSwapBuffers(mainWindow);}
	~MyGLWindow();

private:
	GLFWwindow* mainWindow;
	GLint bufferWidth;
	GLint bufferHeight;
	GLint windowWidth;
	GLint windowHeight;
	bool keys[1024];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;

	static void handleKeys(GLFWwindow *window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow *window, double xPosition, double yPosition);
	void createCallBacks();
};


