#include "MyGLWindow.h"

MyGLWindow::MyGLWindow()
{
	windowWidth = 800;
	windowHeight = 600;
	xChange = 0.0f;
	yChange = 0.0f;
	lastX = 0;
	lastY = 0;
	mouseFirstMoved = true;
	bufferHeight = 0;
	bufferWidth = 0;
	mainWindow = NULL;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = false;
	}
}

MyGLWindow::MyGLWindow(GLint windowWidth, GLint windowHeight)
{
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	bufferHeight = 0;
	bufferWidth = 0;
	xChange = 0;
	yChange = 0;
	lastX = 0;
	lastY = 0;
	mouseFirstMoved = true;
	mainWindow = NULL;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = false;
	}
}

int MyGLWindow::Initialize()
{
	if (!glfwInit())
	{
		printf("Error Initialising GLFW");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW Windows Properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatiblity
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	mainWindow = glfwCreateWindow(windowWidth, windowHeight, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("Error creating GLFW window!");
		glfwTerminate();
		return 1;
	}

	createCallBacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Get buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set the current context
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension access
	glewExperimental = GL_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		printf("Error: %s", glewGetErrorString(error));
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Create Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	glfwSetWindowUserPointer(mainWindow, this);
	return 1;
}

bool* MyGLWindow::getKeys()
{
	return keys;
}

GLfloat MyGLWindow::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat MyGLWindow::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

MyGLWindow::~MyGLWindow()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

void MyGLWindow::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	MyGLWindow* theWindow = static_cast<MyGLWindow*>(glfwGetWindowUserPointer(window));
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			theWindow->keys[key] = false;
		}
	}

}

void MyGLWindow::handleMouse(GLFWwindow* window, double xPosition, double yPosition)
{
	MyGLWindow* theWindow = static_cast<MyGLWindow*>(glfwGetWindowUserPointer(window));
	if (theWindow->mouseFirstMoved) {
		theWindow->lastX = xPosition;
		theWindow->lastY = yPosition;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPosition - theWindow->lastX;
	theWindow->yChange = yPosition - theWindow->lastY;

	theWindow->lastX = xPosition;
	theWindow->lastY = yPosition;
}

void MyGLWindow::createCallBacks()
{
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}
