#pragma once

#include <string>
#include <GL\glew.h>

class Shader
{
public:
	Shader();
	Shader(const std::string& fileName, GLuint *uniforms);

	void Init(const std::string& fileName, GLuint *uniforms);
	void Bind();

	virtual ~Shader();

private:
	static const unsigned int NUM_SHADERS = 2;

	GLuint m_program;
	GLuint m_shader[NUM_SHADERS];
};

