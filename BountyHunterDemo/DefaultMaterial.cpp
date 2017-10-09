///-------------------------------------------------------------------------------------------------
/// File:	DefaultMaterial.cpp.
///
/// Summary:	Implements the default material class.
///-------------------------------------------------------------------------------------------------

#include "DefaultMaterial.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

DefaultMaterial::DefaultMaterial() :
	m_ShaderProgram(nullptr)
{}

DefaultMaterial::~DefaultMaterial()
{}

void DefaultMaterial::Use() const
{
	// activate shader program
	this->m_ShaderProgram->Use();
}

void DefaultMaterial::Unuse() const
{
	this->m_ShaderProgram->Unuse();
}

bool DefaultMaterial::Initialize()
{
	this->m_ShaderProgram = new ShaderProgram(new VertexShader(VERTEXT_SHADER), new FragmentShader(FRAGMENT_SHADER));

	this->m_ShaderProgram->Use();

	glm::mat4 M = glm::translate(glm::mat4(1.0f), glm::vec3(10, 10, 0));

	// ortho 
	glm::mat4 V(1.0f);


	float half_w = 400.0f;
	float half_h = 300.0f;

	float PIXEL_PER_UNIT = 1.0f / 10.0f;

	glm::mat4 P = glm::ortho(-half_w * PIXEL_PER_UNIT, half_w * PIXEL_PER_UNIT, half_h * PIXEL_PER_UNIT, -half_h * PIXEL_PER_UNIT, 0.0f, 100.0f);

	// pers
	//glm::mat4 V = glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//glm::mat4 P = glm::perspective(60.0f, 800.0f / 600.0f, 0.01f, 100.0f);


	glUniformMatrix4fv((*this->m_ShaderProgram)("uModelTransform"), 1, GL_FALSE, (const GLfloat*)&M[0][0]);
	glUniformMatrix4fv((*this->m_ShaderProgram)("uViewTransform"), 1, GL_FALSE, (const GLfloat*)&V[0][0]);
	glUniformMatrix4fv((*this->m_ShaderProgram)("uProjectionTransform"), 1, GL_FALSE, (const GLfloat*)&P[0][0]);
	glGetLastError();
	this->m_ShaderProgram->Unuse();

	return (this->m_ShaderProgram->failed() == false && this->m_ShaderProgram->IsLinked());
}

void DefaultMaterial::Release()
{
	delete this->m_ShaderProgram;
	this->m_ShaderProgram = nullptr;
}
