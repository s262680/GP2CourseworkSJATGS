#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "Common.h"
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
#include "Transform.h"
#include <iostream>
#include "Renderer.h"
#include "Mesh.h"

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
	void loadDiffuseTexture(const string& filename);
	void loadSpecularTexture(const string& filename);
	void loadNormalTexture(const string& filename);
	void loadHeightTexture(const string& filename);

	mat4& getModelMatrix()
	{
		return m_ModelMatrix;
	};
	void rotate(const vec3& delta);
	void copyVertexData(Vertex *pVertex, int numberOfVertices, int *pIndices, int numberOfIndices);
	GLuint getShaderProgram();
private:
	GameObject * m_pParent;
	vector<shared_ptr<GameObject> > m_ChildrenGameObjects;
	mat4 m_ModelMatrix;
	//Shader Program
	GLuint m_Sampler;
	Transform m_GameObjectTransform;
	Renderer m_GameObjectRenderer;
	Mesh m_GameObjectMesh;
};

#endif
