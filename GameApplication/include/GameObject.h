#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "Common.h"
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
#include "Transform.h"
#include <iostream>
#include "Renderer.h"

using namespace std;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void onUpdate();
	void onRender(mat4& view, mat4& projection);
	void onInit();
	void onDestroy();

	void addChild(shared_ptr<GameObject> gameobject);

	//Transform stuff
	void setScale(vec3 scale);
	void setPosition(vec3 pos);
	void setRotation(vec3 rot);

	//RendererStuff
	void loadShaders(const string& vsFilename, const string& fsFilename);
	

	mat4& getModelMatrix()
	{
		return m_ModelMatrix;
	};







	void rotate(const vec3& delta);

	
	
	void copyVertexData(Vertex *pVertex, int numberOfVertices, int *pIndices, int numberOfIndices);

	
	GLuint getShaderProgram();

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




	
	void loadDiffuseTexture(const string& filename);
	void loadSpecularTexture(const string &filename);
	void loadNormalTexture(const string &filename);
	void loadHeightTexture(const string &filename);
private:
	GameObject * m_pParent;
	vector<shared_ptr<GameObject> > m_ChildrenGameObjects;




	mat4 m_ModelMatrix;
	

	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_VAO;
	int m_NumberOfVerts;
	int m_NumberOfIndices;

	//Shader Program
	
	GLuint m_DiffuseTexture;
	GLuint m_SpecularTexture;
	GLuint m_Sampler;
	GLuint m_NormalTexture;
	GLuint m_HeightTexture;

	//Materials
	vec4 m_AmbientMaterialColour;
	vec4 m_DiffuseMaterialColour;
	vec4 m_SpecularMaterialColour;
	float m_SpecularMaterialPower;

	Transform m_GameObjectTransform;
	Renderer m_GameObjectRenderer;
};

#endif
