#pragma once

#include <glad/gl.h>
#include "stb_image.hpp"
#include "Shader.hpp"


class Texture
{
public:
	GLuint ID;
	const char* type;
	GLuint unit;

	Texture(const char* image, const char* texType, GLuint slot);
	Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
};