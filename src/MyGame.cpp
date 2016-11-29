#include "MyGame.h"

const std::string ASSET_PATH = "assets";
const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/textures";
const std::string MODEL_PATH = "/models";

MyGame::MyGame()
{

}

MyGame::~MyGame()
{

}

void MyGame::initScene()
{
	string modelPath = ASSET_PATH + MODEL_PATH + "/Earth.fbx";
	string vsFilename = ASSET_PATH + SHADER_PATH + "/parallaxMappingVS2.glsl";
	string fsFilename = ASSET_PATH + SHADER_PATH + "/parallaxMappingFS2.glsl";
	string diffTextureFileName = ASSET_PATH + TEXTURE_PATH + "/bricks_diff.jpg";
	string specTextureFilename = ASSET_PATH + TEXTURE_PATH + "/bricks_spec.png";
	string normTextureFilename = ASSET_PATH + TEXTURE_PATH + "/bricks_norm.png";
	string heightTextureFilename = ASSET_PATH + TEXTURE_PATH + "/bricks_height.png";
	m_TestGO=shared_ptr<GameObject>(loadModelFromFile(modelPath));
	m_TestGO->loadShaders(vsFilename, fsFilename);
	m_TestGO->loadDiffuseTexture(diffTextureFileName);
	m_TestGO->loadSpecularTexture(specTextureFilename);
	m_TestGO->loadNormalTexture(normTextureFilename);
	m_TestGO->loadHeightTexture(heightTextureFilename);

	m_TestGO->setScale(vec3(5.0f, 5.0f, 5.0f));

	m_CameraPosition = vec3(0.0f, 0.0f, 100.0f);

	m_Light = shared_ptr<Light>(new Light());
	m_Light->DiffuseColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SpecularColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->Direction = vec3(0.0f, 0.0f, -1.0f);
	m_AmbientLightColour = vec4(0.5f, 0.5f, 0.5f, 1.0f);
}

void MyGame::onKeyDown(SDL_Keycode keyCode)
{
	if (keyCode == SDLK_a)
	{
		m_TestGO->rotate(vec3(0.0f, 0.1f, 0.0f));
	}else if (keyCode == SDLK_d)
	{
		m_TestGO->rotate(vec3(0.0f, -0.1f, 0.0f));
	}
	if (keyCode==SDLK_w)
	{
		m_TestGO->rotate(vec3(0.1f,0.0f,0.0f));
	}
	else if (keyCode==SDLK_s)
	{
		m_TestGO->rotate(vec3(-0.1f,0.0f,0.0f));
	}
}

void MyGame::destroyScene()
{
	m_TestGO->onDestroy();
}

void MyGame::update()
{
	GameApplication::update();

	m_ProjMatrix = perspective(radians(45.0f), (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 1000.0f);
	m_ViewMatrix = lookAt(m_CameraPosition, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	m_TestGO->onUpdate();
}

void MyGame::render()
{
	GameApplication::render();
	GLuint currentShader = m_TestGO->getShaderProgram();

	GLint ambientLightColourLocation = glGetUniformLocation(currentShader, "directionLight.ambientColour");
	glUniform4fv(ambientLightColourLocation, 1, value_ptr(m_AmbientLightColour));

	GLint diffuseLightColourLocation = glGetUniformLocation(currentShader, "directionLight.diffuseColour");
	glUniform4fv(diffuseLightColourLocation, 1, value_ptr(m_Light->DiffuseColour));

	GLint specularLightColourLocation = glGetUniformLocation(currentShader, "directionLight.specularColour");
	glUniform4fv(specularLightColourLocation, 1, value_ptr(m_Light->SpecularColour));

	GLint lightDirectionLocation = glGetUniformLocation(currentShader, "directionLight.direction");
	glUniform3fv(lightDirectionLocation, 1, value_ptr(m_Light->Direction));

	GLint cameraPositionLocation = glGetUniformLocation(currentShader, "cameraPos");
	glUniform3fv(cameraPositionLocation, 1, value_ptr(m_CameraPosition));

	m_TestGO->onRender(m_ViewMatrix, m_ProjMatrix);
}
