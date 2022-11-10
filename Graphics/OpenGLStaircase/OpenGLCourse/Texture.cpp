#include "Texture.h"

#include <iostream>

FTexture::FTexture() : TextureID(0), Width(0), Height(0), BitDepth(0), FileLocation(nullptr)
{
}

FTexture::FTexture(char* NewFileLocation) : TextureID(0), Width(0), Height(0), BitDepth(0), FileLocation(NewFileLocation)
{
}

FTexture::~FTexture()
{
	ClearTexture();
}

void FTexture::LoadTexture()
{
	unsigned char* TextureData = stbi_load(FileLocation, &Width, &Height, &BitDepth, 0);

	if (!TextureData)
	{
		std::cout << "Failed to find " << FileLocation << std::endl;
		return;
	}

	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(TextureData);
}

void FTexture::UseTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureID);
}

void FTexture::ClearTexture()
{
	glDeleteTextures(0, &TextureID);
	TextureID = 0;
	Width = 0;
	Height = 0;
	BitDepth = 0;
	FileLocation = nullptr;
}
