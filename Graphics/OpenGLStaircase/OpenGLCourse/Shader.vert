#version 330

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec2 Texture;

out vec4 VectorColor;
out vec2 TextureCoordinate;

uniform mat4 Translate;
uniform mat4 Scale;
uniform mat4 Projection;
uniform mat4 View;
uniform vec3 Offsets[500];

void main()
{
	vec3 Offset = Offsets[gl_InstanceID];
	float W = (2.f * 3.141592f / 36.f) * gl_InstanceID;

	mat4 Rotation = mat4(cos(-W), 0.f, -sin(-W), 0.f,
						 0.f,	 1.f,	  0.f, 0.f,						 
						 sin(-W), 0.f,  cos(-W),  0.f,
						 0.f,    0.f,	  0.f, 1.f);

	mat4 TranslateOffset = mat4(1.f, 0.f, 0.f, 0.f,
						   	    0.f, 1.f, 0.f, 0.f,	
						   	    0.f, 0.f, 1.f, 0.f,
						   	    Offset.x, Offset.y, Offset.z, 1.f);

	gl_Position = Projection * View * Translate * TranslateOffset * Rotation * Scale * vec4(Pos, 1.0);

	VectorColor = vec4(clamp(Pos, 0.f, 1.f), 1.f);

	TextureCoordinate = Texture;
}