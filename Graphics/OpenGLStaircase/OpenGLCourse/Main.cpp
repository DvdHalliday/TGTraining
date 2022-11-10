#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"

const float ToRadians = 3.14159265f / 180.f;

FWindow MainWindow;
std::vector<FMesh*> MeshList;
std::vector<FShader> ShaderList;
FCamera Camera;

glm::vec3 Translations[500];

FTexture WoodTexture;

GLfloat DeltaTime = 0.f;
GLfloat LastTime = 0.f;

// Vertex Shader
static const char* VertexShader = "Shader.vert";

// Fragment Shader
static const char* FragmentShader = "Shader.frag";

void CreateObjects()
{
	unsigned int Indices[] =
	{
		0, 1, 3,
		1, 2, 3,
		0, 7, 4,
		0, 3, 7,
		4, 6, 5,
		4, 7, 6,
		5, 2, 1,
		5, 6, 2,
		3, 2, 6,
		3, 6, 7,
		0, 4, 1,
		1, 4, 5
	};

	GLfloat Vertices[] =
	{
		0.5f , -0.5f,  0.5f,	-1.f, 0.f,
		-0.5f, -0.5f,  0.5f,	1.f, -1.f,
		-0.5f, 0.5f ,  0.5f,	0.f, 0.f,
		0.5f , 0.5f ,  0.5f,	1.f, 0.f,
		0.5f , -0.5f, -0.5f,	0.f, 0.f,
		-0.5f, -0.5f, -0.5f,	1.f, 1.f,
		-0.5f, 0.5f , -0.5f,	0.f, 1.f,
		0.5f , 0.5f , -0.5f,	1.f, 1.f
	};

	for (int i = 0; i < 500; i++)
	{
		Translations[i] = glm::vec3(cosf(static_cast<float>(i) * 2.f * 3.141592f /36.f) * 2.f, static_cast<float>(i) * 0.1f, 2.f * sinf(static_cast<float>(i) * 2.f * 3.141592f / 36.f));
	}

	FMesh* Object = new FMesh();
	Object->CreateMesh(Vertices, Indices, 40, 36, Translations);
	MeshList.push_back(Object);

}

void CreateShaders()
{
	FShader* FirstShader = new FShader();
	FirstShader->CreateFromFiles(VertexShader, FragmentShader);
	ShaderList.push_back(*FirstShader);
}

int main()
{
	MainWindow = FWindow(1920, 1080);
	MainWindow.Initialize();

	CreateObjects();
	CreateShaders();

	Camera = FCamera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f), -90.f, 0.f, 5.f, .5f);

	WoodTexture = FTexture((char*)"D:/GitHub/TGTraining/Graphics/OpenGLStaircase/Textures/wood.jpg");
	WoodTexture.LoadTexture();
	WoodTexture.UseTexture();

	glm::mat4 Projection = glm::perspective(45.f, (GLfloat)MainWindow.GetBufferWidth() / (GLfloat)MainWindow.GetBufferHeight(), .1f, 100.f);

	// Loop until window is closed
	while (!MainWindow.GetShouldClose())
	{
		GLfloat Now = glfwGetTime();
		DeltaTime = Now - LastTime;
		LastTime = Now;

		// Get & handle user input events
		glfwPollEvents();

		Camera.KeyControl(MainWindow.GetKeys(), DeltaTime);
		Camera.MouseControl(MainWindow.GetXChange(), MainWindow.GetYChange());

		// Clear window
		glClearColor(0.878431f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ShaderList[0].UseShader();

		glm::mat4 Translate(1.f);
		glm::mat4 Scale(1.f);

		Translate = glm::translate(Translate, glm::vec3(0.f, 0.f, -2.5f));
		//Model = glm::rotate(Model, CurrentAngle * ToRadians, glm::vec3(0.f, 1.f, 0.f));
		Scale = glm::scale(Scale, glm::vec3(2.f, 0.1f, 0.5f));


		glUniformMatrix4fv(ShaderList[0].GetTranslateLocation(), 1, GL_FALSE, glm::value_ptr(Translate));
		glUniformMatrix4fv(ShaderList[0].GetScaleLocation(), 1, GL_FALSE, glm::value_ptr(Scale));
		glUniformMatrix4fv(ShaderList[0].GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(Projection));
		glUniformMatrix4fv(ShaderList[0].GetViewLocation(), 1, GL_FALSE, glm::value_ptr(Camera.CalculateViewMatrix()));

		for (int i = 0; i < 500; i++)
		{
			glUniform3fv(ShaderList[0].GetOffsetLocationAt(i), 1, glm::value_ptr(Translations[i]));
		}

		WoodTexture.UseTexture();

		MeshList[0]->RenderMesh();

		glUseProgram(0);

		MainWindow.SwapBuffers();
	}
}