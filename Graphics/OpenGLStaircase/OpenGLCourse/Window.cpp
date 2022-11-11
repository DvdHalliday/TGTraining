#include "Window.h"

void FWindow::HandleKeys(GLFWwindow* Window, int Key, int Code, int Action, int Mode)
{
	FWindow* TheWindow = static_cast<FWindow*>(glfwGetWindowUserPointer(Window));

	if(Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(Window, GL_TRUE);
	}

	if(Key >= 0 && Key < 1024)
	{
		if(Action == GLFW_PRESS)
		{
			TheWindow->Keys[Key] = true;
		}
		else if(Action == GLFW_RELEASE)
		{
			TheWindow->Keys[Key] = false;
		}
	}
}

void FWindow::CreateCallbacks()
{
	glfwSetKeyCallback(MainWindow, HandleKeys);
	glfwSetCursorPosCallback(MainWindow, HandleMouse);
}

void FWindow::HandleMouse(GLFWwindow* Window, double XPosition, double YPosition)
{
	FWindow* TheWindow = static_cast<FWindow*>(glfwGetWindowUserPointer(Window));

	if (TheWindow->bIsMouseFirstMovement)
	{
		TheWindow->LastX = XPosition;
		TheWindow->LastY = YPosition;
		TheWindow->bIsMouseFirstMovement = false;
	}

	TheWindow->XChange = XPosition - TheWindow->LastX;
	TheWindow->YChange = -(YPosition - TheWindow->LastY);

	TheWindow->LastX = XPosition;
	TheWindow->LastY = YPosition;
}

FWindow::FWindow() : Width(800), Height(600), XChange(0.f), YChange(0.f)
{
	std::fill(Keys, std::end(Keys), false);
}

FWindow::FWindow(GLint WindowWidth, GLint WindowHeight) : Width(WindowWidth), Height(WindowHeight), XChange(0.f), YChange(0.f)
{
	std::fill(Keys, std::end(Keys), false);
}

FWindow::~FWindow()
{
	glfwDestroyWindow(MainWindow);
	glfwTerminate();
}

void FWindow::Initialize()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		std::cout << "GLFW initialisation failed!" << std::endl;
		glfwTerminate();
		return;
	}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core profile - No backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	MainWindow = glfwCreateWindow(Width, Height, "Test Window", NULL, NULL);
	if (!MainWindow)
	{
		std::cout << "GLFW window creation failed!" << std::endl;
		glfwTerminate();
		return;
	}

	// Get Buffer size information
	glfwGetFramebufferSize(MainWindow, &BufferWidth, &BufferHeight);

	// Set context for GLEW to use 
	glfwMakeContextCurrent(MainWindow);

	// Handle Key & Mouse input
	CreateCallbacks();
	glfwSetInputMode(MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLFW window creation failed!" << std::endl;
		glfwDestroyWindow(MainWindow);
		glfwTerminate();
		return;
	}

	glEnable(GL_DEPTH_TEST);

	// Create viewport
	glViewport(0, 0, BufferWidth, BufferHeight);

	glfwSetWindowUserPointer(MainWindow, this);
}

GLint FWindow::GetBufferWidth()
{
	return BufferWidth;
}

GLint FWindow::GetBufferHeight()
{
	return BufferHeight;
}

bool FWindow::GetShouldClose()
{
	return glfwWindowShouldClose(MainWindow);
}

bool* FWindow::GetKeys()
{
	return Keys;
}

GLfloat FWindow::GetXChange()
{
	GLfloat TheChange = XChange;
	XChange = 0.f;
	return TheChange;
}

GLfloat FWindow::GetYChange()
{
	GLfloat TheChange = YChange;
	YChange = 0.f;
	return TheChange;
}

void FWindow::SwapBuffers()
{
	glfwSwapBuffers(MainWindow);
}
