#include "Mesh.h"

FMesh::FMesh()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;

	IndexCount = 0;
}

FMesh::~FMesh()
{
	ClearMesh();
}

void FMesh::CreateMesh(GLfloat* Vertices, unsigned int* Indices, unsigned int NumberOfVertices, unsigned int NumberOfIndices, glm::vec3* Translations)
{
	IndexCount = NumberOfIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * NumberOfIndices, Indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices[0]) * NumberOfVertices, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices[0]) * 5, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices[0]) * 5, (void*)(sizeof(Vertices[0]) * 3));
	glEnableVertexAttribArray(1);

	GLuint InstanceVBO;
	glGenBuffers(1, &InstanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, InstanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Translations[0]) * 500, Translations, GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, InstanceVBO);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribDivisor(2, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void FMesh::RenderMesh()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElementsInstanced(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, 0, 500);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void FMesh::ClearMesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteBuffers(1, &VAO);
		VAO = 0;
	}

	IndexCount = 0;
}
