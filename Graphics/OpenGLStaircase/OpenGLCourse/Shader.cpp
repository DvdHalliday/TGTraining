#include "Shader.h"

void FShader::CompileShader(const char* VertexCode, const char* FragmentCode)
{
	ID = glCreateProgram();

	if (!ID)
	{
		std::cout << "Error creating shader program" << std::endl;
		return;
	}

	AddShader(ID, VertexCode, GL_VERTEX_SHADER);
	AddShader(ID, FragmentCode, GL_FRAGMENT_SHADER);

	GLint Result = 0;
	GLchar ELog[1024] = { 0 };

	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &Result);

	if (!Result)
	{
		glGetProgramInfoLog(ID, sizeof ELog, NULL, ELog);
		std::cout << "Error linking program: " << ELog << std::endl;
		return;
	}

	glValidateProgram(ID);
	glGetProgramiv(ID, GL_VALIDATE_STATUS, &Result);

	if (!Result)
	{
		glGetProgramInfoLog(ID, sizeof ELog, NULL, ELog);
		std::cout << "Error validating program: " << ELog << std::endl;
		return;
	}

	UniformTranslate = glGetUniformLocation(ID, "Translate");
	UniformScale = glGetUniformLocation(ID, "Scale");
	UniformProjection = glGetUniformLocation(ID, "Projection");
	UniformView = glGetUniformLocation(ID, "View");
	UniformOffsets = glGetUniformLocation(ID, "Offsets");
}

void FShader::AddShader(GLuint TheProgram, const char* ShaderCode, GLenum EShaderType)
{
	GLuint TheShader = glCreateShader(EShaderType);

	const GLchar* TheCode[1];
	TheCode[0] = ShaderCode;

	GLint CodeLength[1];
	CodeLength[0] = strlen(ShaderCode);

	glShaderSource(TheShader, 1, TheCode, CodeLength);
	glCompileShader(TheShader);

	GLint Result = 0;
	GLchar ELog[1024] = { 0 };

	glGetShaderiv(TheShader, GL_COMPILE_STATUS, &Result);

	if (!Result)
	{
		glGetShaderInfoLog(TheShader, sizeof ELog, NULL, ELog);
		std::cout << "Error compiling the " << EShaderType << " shader: " << ELog << std::endl;
		return;
	}

	glAttachShader(TheProgram, TheShader);
}

FShader::FShader() : ID(0), UniformProjection(0), UniformTranslate(0), UniformScale(0), UniformView(0), UniformOffsets(0)
{
}

FShader::~FShader()
{
	ClearShader();
}

void FShader::CreateFromString(const char* VertexCode, const char* FragmentCode)
{
	CompileShader(VertexCode, FragmentCode);
}

GLuint FShader::GetProjectionLocation()
{
	return UniformProjection;
}

GLuint FShader::GetTranslateLocation()
{
	return UniformTranslate;
}

GLuint FShader::GetScaleLocation()
{
	return UniformScale;
}

GLuint FShader::GetViewLocation()
{
	return UniformView;
}

GLuint FShader::GetOffsetsLocation()
{
	return UniformOffsets;
}

GLuint FShader::GetOffsetLocationAt(int Index)
{
	return glGetUniformLocation(ID, (("Offsets[" + std::to_string(Index)) + "]").c_str());
}

void FShader::UseShader()
{
	glUseProgram(ID);
}

void FShader::ClearShader()
{
	if (ID != 0)
	{
		glDeleteProgram(ID);
		ID = 0;
	}

	UniformProjection = 0;
	UniformTranslate = 0;
	UniformScale = 0;
	UniformView = 0;
	UniformOffsets = 0;
}

void FShader::CreateFromFiles(const char* VertexLocation, const char* FragmentLocation)
{
	std::string VertexString = ReadFile(VertexLocation);
	std::string FragmentString = ReadFile(FragmentLocation);
	const char* VertexCode = VertexString.c_str();
	const char* FragmentCode = FragmentString.c_str();

	CompileShader(VertexCode, FragmentCode);
}

std::string FShader::ReadFile(const char* FileLocation)
{
	std::string Content;
	std::ifstream FileStream(FileLocation, std::ios::in);

	if (!FileStream.is_open())
	{
		std::cout << "Failed to read " << FileLocation << std::endl;
		return "";
	}

	std::string Line = "";
	while (!FileStream.eof())
	{
		std::getline(FileStream, Line);
		Content.append(Line + "\n");
	}

	FileStream.close();
	return Content;
}
