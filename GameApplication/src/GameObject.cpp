#include "GameObject.h"

GameObject::GameObject()
{
	
	

	m_ModelMatrix = mat4(1.0f);
	


	m_VBO=0;
	m_EBO=0;
	m_VAO=0;
	m_NumberOfVerts=0;
	m_NumberOfIndices=0;

	//Shader Program

	
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


	
	//m_ModelMatrix = m_GameObjectTransform.getModelMatrix();
	m_ModelMatrix = m_GameObjectTransform.getTranslationMatrix()*m_GameObjectTransform.getRotationMatrix()*m_GameObjectTransform.getScaleMatrix(); //MARKER FOR WHERE WE DID STUFF!!!!!!!!!!!!!!!
	if (m_pParent)
	{
		m_ModelMatrix *= m_pParent->getModelMatrix();
	}

	// And this is where we proved we're not retarded m_GameObjectTransform.TransformUpdate();

}

void GameObject::onRender(mat4& view, mat4& projection)
{
	GLuint shaderProgram = m_GameObjectRenderer.getShaderProgram();
	glUseProgram(shaderProgram);
	glBindVertexArray(m_VAO);

	GLint MVPLocation = glGetUniformLocation(shaderProgram, "MVP");
	mat4 MVP = projection*view*m_ModelMatrix;
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));

	GLint ModelLocation = glGetUniformLocation(shaderProgram, "Model");
	glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix));

	glBindSampler(0, m_Sampler);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_GameObjectRenderer.getDiffuseTexture());
	GLint specTextureLocation = glGetUniformLocation(shaderProgram, "diffuseSampler");
	glUniform1i(specTextureLocation, 0);

	glBindSampler(1, m_Sampler);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_GameObjectRenderer.getSpecularTexture());
	GLint diffTextureLocation = glGetUniformLocation(shaderProgram, "specularSampler");
	glUniform1i(diffTextureLocation, 1);

	glBindSampler(2, m_Sampler);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_GameObjectRenderer.getNormalTexture());
	GLint normTextureLocation = glGetUniformLocation(shaderProgram, "normalSampler");
	glUniform1i(normTextureLocation, 2);

	glBindSampler(3, m_Sampler);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_GameObjectRenderer.getHeightTexture());
	GLint heightTextureLocation = glGetUniformLocation(shaderProgram, "heightMap");
	glUniform1i(heightTextureLocation, 3);


	GLint ambientLocation = glGetUniformLocation(shaderProgram, "ambientMaterialColour");
	glUniform4fv(ambientLocation, 1, value_ptr(m_GameObjectRenderer.getAmbientMaterialColour()));

	GLint diffuseLocation = glGetUniformLocation(shaderProgram, "diffuseMaterialColour");
	glUniform4fv(diffuseLocation, 1, value_ptr(m_GameObjectRenderer.getDiffuseMaterialColour()));
	//glUniform4fv(diffuseLocation, 1, value_ptr(m_DiffuseMaterialColour));

	GLint specularLocation = glGetUniformLocation(shaderProgram, "specularMaterialColour");
	glUniform4fv(specularLocation, 1, value_ptr(m_GameObjectRenderer.getSpecularMaterialColour()));

	GLint specularPowerLocation = glGetUniformLocation(shaderProgram, "specularPower");
	glUniform1f(specularPowerLocation, m_GameObjectRenderer.getSpecularPower());

	glDrawElements(GL_TRIANGLES, m_NumberOfIndices, GL_UNSIGNED_INT, NULL);
}

void GameObject::onInit()
{

}

void GameObject::onDestroy()
{
	glDeleteVertexArrays(1, &m_VAO);

	
	glDeleteBuffers(1, &m_EBO);
	glDeleteBuffers(1, &m_VBO);
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
	m_NumberOfVerts = numberOfVertices;
	m_NumberOfIndices = numberOfIndices;
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(Vertex), pVertex, GL_STATIC_DRAW);

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(int), pIndices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void**)(offsetof(Vertex, colours)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void**)(offsetof(Vertex, texCoords0)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void**)(offsetof(Vertex, normal)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void**)(offsetof(Vertex, tangent)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void**)(offsetof(Vertex, binormal)));

}

GLuint GameObject::getShaderProgram()
{
	return m_GameObjectRenderer.getShaderProgram();
}

