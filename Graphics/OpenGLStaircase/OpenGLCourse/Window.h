#pragma once

#include<iostream>

#include<GL\glew.h>
#include<GLFW\glfw3.h>

class FWindow
{
private:
	GLFWwindow* MainWindow;

	GLint Width;
	GLint Height;

	GLint BufferWidth;
	GLint BufferHeight;

	bool Keys[1024];
	static void HandleKeys(GLFWwindow* Window, int Key, int Code, int Action, int Mode);
	void CreateCallbacks();

	GLfloat LastX;
	GLfloat LastY;
	GLfloat XChange;
	GLfloat YChange;

	bool bIsMouseFirstMovement = true;

	static void HandleMouse(GLFWwindow* Window, double XPosition, double YPosition);

public:
	FWindow();
	FWindow(GLint WindowWidth, GLint WindowHeight);
	~FWindow();

	void Initialize();

	GLint GetBufferWidth();
	GLint GetBufferHeight();

	bool GetShouldClose();

	bool* GetKeys();
	GLfloat GetXChange();
	GLfloat GetYChange();

	void SwapBuffers();
};

