///-------------------------------------------------------------------------------------------------
/// File:	LineMaterial.cpp.
///
/// Summary:	Implements the line material class.
///-------------------------------------------------------------------------------------------------

#include "LineMaterial.h"

LineMaterial::LineMaterial() :
	m_ShaderProgram(nullptr)
{
}

LineMaterial::~LineMaterial()
{
}

void LineMaterial::Use() const
{
	this->m_ShaderProgram->Use();
}

void LineMaterial::Unuse() const
{
	this->m_ShaderProgram->Unuse();
}

bool LineMaterial::Initialize()
{
	this->m_ShaderProgram = new ShaderProgram(new VertexShader(VERTEXT_SHADER), new FragmentShader(FRAGMENT_SHADER));
	return (this->m_ShaderProgram->failed() == false && this->m_ShaderProgram->IsLinked());
}

void LineMaterial::Release()
{
	delete this->m_ShaderProgram;
	this->m_ShaderProgram = nullptr;
}
