///-------------------------------------------------------------------------------------------------
/// File:	DefaultMaterial.cpp.
///
/// Summary:	Implements the default material class.
///-------------------------------------------------------------------------------------------------

#include "DefaultMaterial.h"
#include "GLShader.h"

DefaultMaterial::DefaultMaterial() :
	m_ShaderProgram(nullptr)
{}

DefaultMaterial::~DefaultMaterial()
{}

void DefaultMaterial::Use() const
{
	this->m_ShaderProgram->Use();
}

void DefaultMaterial::Unuse() const
{
	this->m_ShaderProgram->Unuse();
}

bool DefaultMaterial::Initialize()
{
	this->m_ShaderProgram = new ShaderProgram(new VertexShader(VERTEXT_SHADER), new FragmentShader(FRAGMENT_SHADER));
	return (this->m_ShaderProgram->failed() == false && this->m_ShaderProgram->IsLinked());
}

void DefaultMaterial::Release()
{
	delete this->m_ShaderProgram;
	this->m_ShaderProgram = nullptr;
}
