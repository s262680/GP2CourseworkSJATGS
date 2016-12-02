#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "Common.h"
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
#include "Transform.h"
#include "Material.h"
#include <iostream>

class Material
{
public:
	Material();
	~Material();

private:

	vec4 m_AmbientMaterialColour;
	vec4 m_DiffuseMaterialColour;
	vec4 m_SpecularMaterialColour;
	float m_SpecularMaterialPower;

};


#endif