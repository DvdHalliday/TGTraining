#version 330

in vec4 VectorColor;
in vec2 TextureCoordinate;

out vec4 Color;

uniform sampler2D TheTexture;

void main()
{
	Color = texture(TheTexture, TextureCoordinate);
}