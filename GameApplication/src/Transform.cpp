#include "..\include\Transform.h"
#include <iostream>

using namespace std;

Transform::Transform()
{
	m_Scale = vec3(1.0f, 1.0f, 1.0f);
	m_Position = vec3(0.0f, 0.0f, 0.0f);
	m_ScaleMatrix = mat4(1.0f);
	m_TranslationMatrix = mat4(1.0f);
}

Transform::~Transform()
{
}



void Transform::TransformUpdate()
{
	/*
	cout << "Test";
	std::cout << glm::to_string(m_Scale) << std::endl;
	*/
	m_ScaleMatrix = scale(m_Scale);
	m_RotationMatrix = eulerAngleYXZ(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	m_TranslationMatrix = translate(getPosition());
	
}
