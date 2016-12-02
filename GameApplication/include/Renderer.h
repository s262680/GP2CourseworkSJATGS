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

	void onRender(mat4& view, mat4& projection, GLuint VAO, mat4& modelMatrix, int numberOfIndices);

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

	vec4 getAmbientMaterialColour()
	{
		return m_AmbientMaterialColour;
	};
	vec4 getDiffuseMaterialColour()
	{
		return m_DiffuseMaterialColour;
	};
	vec4 getSpecularMaterialColour()
	{
		return m_SpecularMaterialColour;
	};
	float getSpecularPower()
	{
		return m_SpecularMaterialPower;
	};

	void loadDiffuseTexture(const string& filename);
	void loadSpecularTexture(const string& filename);
	void loadNormalTexture(const string& filename);
	void loadHeightTexture(const string& filename);

	void setAmbientMaterialColour(const vec4& colour)
	{
		m_AmbientMaterialColour = colour;
	};

	void setDiffuseMaterialColour(const vec4& colour)
	{
		m_DiffuseMaterialColour = colour;
	};

	void setSpecularMaterialColour(const vec4& colour)
	{
		m_SpecularMaterialColour = colour;
	};

	void setSpecularPower(float power)
	{
		m_SpecularMaterialPower = power;
	};

private:

	GLuint m_ShaderProgram;

	GLuint m_Sampler;
	GLuint m_DiffuseTexture;
	GLuint m_SpecularTexture;
	GLuint m_NormalTexture;
	GLuint m_HeightTexture;

	//Materials
	vec4 m_AmbientMaterialColour;
	vec4 m_DiffuseMaterialColour;
	vec4 m_SpecularMaterialColour;
	float m_SpecularMaterialPower;
};

#endif