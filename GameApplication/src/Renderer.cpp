#include "..\include\Renderer.h"
#include <iostream>


Renderer::Renderer()
{
	m_ShaderProgram = 0;
	m_DiffuseTexture = 0;
	m_SpecularTexture =0;
	m_NormalTexture=0;
	m_HeightTexture=0;

	m_AmbientMaterialColour = vec4(0.2f, 0.2f, 0.2f, 1.0f);
	m_DiffuseMaterialColour = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	m_SpecularMaterialColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	m_SpecularMaterialPower = 25.0f;

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

void Renderer::onRender(mat4& view, mat4& projection, GLuint VAO, mat4& modelMatrix, int numberOfIndices)
{

	GLuint shaderProgram = m_ShaderProgram;
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);

	GLint MVPLocation = glGetUniformLocation(shaderProgram, "MVP");
	mat4 MVP = projection*view*modelMatrix;
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));

	GLint ModelLocation = glGetUniformLocation(shaderProgram, "Model");
	glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glBindSampler(0, m_Sampler);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_DiffuseTexture);
	GLint specTextureLocation = glGetUniformLocation(shaderProgram, "diffuseSampler");
	glUniform1i(specTextureLocation, 0);

	glBindSampler(1, m_Sampler);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_SpecularTexture);
	GLint diffTextureLocation = glGetUniformLocation(shaderProgram, "specularSampler");
	glUniform1i(diffTextureLocation, 1);

	glBindSampler(2, m_Sampler);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_NormalTexture);
	GLint normTextureLocation = glGetUniformLocation(shaderProgram, "normalSampler");
	glUniform1i(normTextureLocation, 2);

	glBindSampler(3, m_Sampler);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D,m_HeightTexture);
	GLint heightTextureLocation = glGetUniformLocation(shaderProgram, "heightMap");
	glUniform1i(heightTextureLocation, 3);


	GLint ambientLocation = glGetUniformLocation(shaderProgram, "ambientMaterialColour");
	glUniform4fv(ambientLocation, 1, value_ptr(m_AmbientMaterialColour));

	GLint diffuseLocation = glGetUniformLocation(shaderProgram, "diffuseMaterialColour");
	glUniform4fv(diffuseLocation, 1, value_ptr(m_DiffuseMaterialColour));
	//glUniform4fv(diffuseLocation, 1, value_ptr(m_DiffuseMaterialColour));

	GLint specularLocation = glGetUniformLocation(shaderProgram, "specularMaterialColour");
	glUniform4fv(specularLocation, 1, value_ptr(m_SpecularMaterialColour));

	GLint specularPowerLocation = glGetUniformLocation(shaderProgram, "specularPower");
	glUniform1f(specularPowerLocation, m_SpecularMaterialPower);

	glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, NULL);

}


