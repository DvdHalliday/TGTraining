#pragma once

#include <GL\glew.h>
#include "stb_image.h"

class FTexture
{
private:
	GLuint TextureID;
	int Width;
	int Height;
	int BitDepth;
	char* FileLocation;

public:
	FTexture();
	FTexture(char* NewFileLocation);
	~FTexture();

	void LoadTexture();
	void UseTexture();
	void ClearTexture();
};

