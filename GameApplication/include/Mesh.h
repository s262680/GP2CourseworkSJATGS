#ifndef _MESH_H
#define _MESH_H

#include "Common.h"
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
#include "Transform.h"
#include <iostream>

class Mesh
{
public:
	Mesh();
	~Mesh();

	GLuint getVAO()
	{
		return m_VAO;
	}

	void onDestroy();

	int getNumberOfIndices()
	{
		return m_NumberOfIndices;
	}

	void copyVertexData(Vertex *pVertex, int numberOfVertices, int *pIndices, int numberOfIndices);

private:
	int m_NumberOfVerts;
	int m_NumberOfIndices;

	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_VAO;
};


#endif