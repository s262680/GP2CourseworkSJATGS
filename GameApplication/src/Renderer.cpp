#include "..\include\Renderer.h"
#include <iostream>


Renderer::Renderer()
{
	m_ShaderProgram = 0;

}

Renderer::~Renderer()
{
}

void Renderer::loadShaders(const string & vsFilename, const string & fsFilename)
{
	GLuint vertexShaderProgram = loadShaderFromFile(vsFilename, VERTEX_SHADER);

	GLuint fragmentShaderProgram = loadShaderFromFile(fsFilename, FRAGMENT_SHADER);

	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShaderProgram);
	glAttachShader(m_ShaderProgram, fragmentShaderProgram);
	glLinkProgram(m_ShaderProgram);
	checkForLinkErrors(m_ShaderProgram);

	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);

	logShaderInfo(m_ShaderProgram);
}

void Renderer::onDestroy()
{
	glDeleteProgram(m_ShaderProgram);
}
