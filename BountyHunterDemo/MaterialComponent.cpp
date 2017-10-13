///-------------------------------------------------------------------------------------------------
/// File:	MaterialComponent.cpp.
///
/// Summary:	Implements the material component class.
///-------------------------------------------------------------------------------------------------

#include "MaterialComponent.h"

const Color4f MaterialComponent::DEFAULT_COLOR0(0.8f, 0.8f, 8.0f, 1.0f);

MaterialComponent::MaterialComponent(const Material& material, Color4f color) : 
	Material(material),
	m_Color0(color)
{}

MaterialComponent::~MaterialComponent()
{}

void MaterialComponent::Apply()
{
	SetUniform4fv(SHADER_UNIFORM_COLOR0, (const float*)&this->m_Color0[0]);
}
