#include "..\include\Material.h"
#include <iostream>
#include "Material.h"

Material::Material()
{

	m_AmbientMaterialColour = vec4(0.2f, 0.2f, 0.2f, 1.0f);
	m_DiffuseMaterialColour = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	m_SpecularMaterialColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	m_SpecularMaterialPower = 25.0f;

}

Material::~Material()
{
}
