#pragma once
#include <GL\glew.h>
#include <glm/vec3.hpp>

class FMesh
{
private:
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;
	GLsizei IndexCount;

public:
	FMesh();
	~FMesh();

	void CreateMesh(GLfloat* Vertices, unsigned int* Indices, unsigned int NumberOfVertices, unsigned int NumberOfIndices, glm::vec3* Translations);
	void RenderMesh();
	void ClearMesh();
};

