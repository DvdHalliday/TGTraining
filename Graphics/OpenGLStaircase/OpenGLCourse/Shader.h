#pragma once

#include<iostream>
#include<string>
#include<fstream>

#include<GL/glew.h>

class FShader
{
private:
	GLuint ID;
	GLuint UniformProjection;
	GLuint UniformTranslate;
	GLuint UniformScale;
	GLuint UniformView;
	GLuint UniformOffsets;

	void CompileShader(const char* VertexCode, const char* FragmentCode);
	void AddShader(GLuint TheProgram, const char* ShaderCode, GLenum EShaderType);

public:
	FShader();
	~FShader();

	void CreateFromString(const char* VertexCode, const char* FragmentCode);

	GLuint GetProjectionLocation();
	GLuint GetTranslateLocation();
	GLuint GetScaleLocation();
	GLuint GetViewLocation();
	GLuint GetOffsetsLocation();
	GLuint GetOffsetLocationAt(int Index);

	void UseShader();
	void ClearShader();

	void CreateFromFiles(const char* VertexLocation, const char* FragmentLocation);
	std::string ReadFile(const char* FileLocation);
};

