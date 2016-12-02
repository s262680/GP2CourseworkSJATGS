#include "..\include\Renderer.h"
#include <iostream>


Renderer::Renderer()
{
	m_ShaderProgram = 0;
	m_DiffuseTexture = 0;

	m_Sampler=0;
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

void Renderer::loadDiffuseTexture(const string & filename)
{
	m_DiffuseTexture = loadTextureFromFile(filename);
	glBindTexture(GL_TEXTURE_2D, m_DiffuseTexture);
	glGenerateMipmap(GL_TEXTURE_2D);

	glGenSamplers(1, &m_Sampler);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);

}
void Renderer::loadSpecularTexture(const string & filename)
{
	m_SpecularTexture = loadTextureFromFile(filename);
	glBindTexture(GL_TEXTURE_2D, m_SpecularTexture);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Renderer::loadNormalTexture(const string & filename)
{
	m_NormalTexture = loadTextureFromFile(filename);
	glBindTexture(GL_TEXTURE_2D, m_NormalTexture);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Renderer::loadHeightTexture(const string & filename)
{
	m_HeightTexture = loadTextureFromFile(filename);
	glBindTexture(GL_TEXTURE_2D, m_HeightTexture);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Renderer::onDestroy()
{
	glDeleteTextures(1, &m_DiffuseTexture);
	glDeleteProgram(m_ShaderProgram);
}


