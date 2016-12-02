#ifndef _RENDERER_H
#define _RENDERER_H

#include "Common.h"
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
#include "Transform.h"
#include <iostream>

class Renderer
{
public:
	Renderer();
	~Renderer();

	void loadShaders(const string& vsFilename, const string& fsFilename);
	void onDestroy();

	GLuint getShaderProgram()
	{
		return m_ShaderProgram;
	};

	GLuint getDiffuseTexture()
	{
		return m_DiffuseTexture;
	};
	GLuint getSpecularTexture()
	{
		return m_SpecularTexture;
	};
	GLuint getNormalTexture()
	{
		return m_NormalTexture;
	};
	GLuint getHeightTexture()
	{
		return m_HeightTexture;
	};

	void loadDiffuseTexture(const string& filename);
	void loadSpecularTexture(const string& filename);
	void loadNormalTexture(const string& filename);
	void loadHeightTexture(const string& filename);

private:

	GLuint m_ShaderProgram;

	GLuint m_Sampler;
	GLuint m_DiffuseTexture;
	GLuint m_SpecularTexture;
	GLuint m_NormalTexture;
	GLuint m_HeightTexture;
};

#endif