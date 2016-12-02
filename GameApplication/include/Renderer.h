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

private:

	GLuint m_ShaderProgram;
};

#endif