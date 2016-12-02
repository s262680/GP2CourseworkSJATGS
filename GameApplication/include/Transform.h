#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Common.h"
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
#include "Transform.h"
#include <iostream>

class Transform
{
public:

	Transform();
	~Transform();


	void setScale(const vec3& scale)
	{
		m_Scale = scale;
	};

	vec3& getScale()
	{
		return m_Scale;
	};

	mat4& getScaleMatrix()
	{
		return m_ScaleMatrix;
	};

	mat4& getRotationMatrix()
	{
		return m_RotationMatrix;
	};

	mat4& getTranslationMatrix()
	{
		return m_TranslationMatrix;
	};

	void setPosition(const vec3& pos)
	{
		m_Position = pos;
	};

	void setRotation(const vec3& rot)
	{
		m_Rotation = rot;
	};

	vec3& getPosition()
	{
		return m_Position;
	};

	vec3& getRotation()
	{
		return m_Rotation;
	};

	void TransformUpdate();

private:

	vec3 m_Scale;
	vec3 m_Position;
	vec3 m_Rotation;

	mat4 m_ScaleMatrix;
	mat4 m_RotationMatrix;
	mat4 m_TranslationMatrix;

};

#endif