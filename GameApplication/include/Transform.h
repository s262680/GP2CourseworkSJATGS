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

	void setPosition(const vec3& pos)
	{
		m_Position = pos;
	};

	vec3& getPosition()
	{
		return m_Position;
	};

	void TransformUpdate();

private:

	vec3 m_Scale;
	vec3 m_Position;

	mat4 m_ScaleMatrix;
};

#endif