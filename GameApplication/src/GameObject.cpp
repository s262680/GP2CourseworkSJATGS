#include "GameObject.h"

GameObject::GameObject()
{
	m_ModelMatrix = mat4(1.0f);

	m_Sampler=0;
	m_pParent = nullptr;
}

GameObject::~GameObject()
{
}
void GameObject::onUpdate()
{
	//mat4 rotationXMatrix = ::rotate(radians(m_Rotation.x), vec3(1.0f, 0.0f, 0.0f));
	//mat4 rotationYMatrix = ::rotate(radians(m_Rotation.y), vec3(0.0f, 1.0f, 0.0f));
	//mat4 rotationZMatrix = ::rotate(radians(m_Rotation.z), vec3(0.0f, 0.0f, 1.0f));
	//m_RotationMatrix = rotationXMatrix*rotationYMatrix*rotationZMatrix;
	m_GameObjectTransform.TransformUpdate(); 

	m_ModelMatrix = m_GameObjectTransform.getModelMatrix();
	if (m_pParent)
	{
		m_ModelMatrix *= m_pParent->getModelMatrix();
	}
	// And this is where we proved we're not retarded m_GameObjectTransform.TransformUpdate();
}

void GameObject::onRender(mat4& view, mat4& projection)
{
	GLuint VAO = m_GameObjectMesh.getVAO ();
	GLuint numberOfVertices = m_GameObjectMesh.getNumberOfIndices();
	m_GameObjectRenderer.onRender(view, projection, VAO, m_ModelMatrix, numberOfVertices);
}

void GameObject::onInit()
{
}

void GameObject::onDestroy()
{
	m_GameObjectMesh.onDestroy();
	glDeleteSamplers(1, &m_Sampler);
	m_GameObjectRenderer.onDestroy();
}

void GameObject::addChild(shared_ptr<GameObject> gameobject)
{
	gameobject->m_pParent = this;
	m_ChildrenGameObjects.push_back(gameobject);
}

void GameObject::rotate(const vec3 & delta)
{
	//m_Rotation += delta;
}

void GameObject::setScale(vec3 scale)
{
	m_GameObjectTransform.setScale(scale);
}

void GameObject::setPosition(vec3 pos)
{
	m_GameObjectTransform.setPosition(pos);
}

void GameObject::setRotation(vec3 rot)
{
	m_GameObjectTransform.setRotation(rot);
}

void GameObject::loadShaders(const string & vsFilename, const string & fsFilename)
{
	m_GameObjectRenderer.loadShaders(vsFilename, fsFilename);
}

void GameObject::loadDiffuseTexture(const string & filename)
{
	m_GameObjectRenderer.loadDiffuseTexture(filename);
}

void GameObject::loadSpecularTexture(const string & filename)
{
	m_GameObjectRenderer.loadSpecularTexture(filename);
}

void GameObject::loadNormalTexture(const string & filename)
{
	m_GameObjectRenderer.loadNormalTexture(filename);
}

void GameObject::loadHeightTexture(const string & filename)
{
	m_GameObjectRenderer.loadHeightTexture(filename);
}

void GameObject::copyVertexData(Vertex * pVertex, int numberOfVertices, int * pIndices, int numberOfIndices)
{
	m_GameObjectMesh.copyVertexData(pVertex, numberOfVertices, pIndices, numberOfIndices);
}

GLuint GameObject::getShaderProgram()
{
	return m_GameObjectRenderer.getShaderProgram();
}

