/** Shader.cpp

	Author : Tobias Stein
	Created: 03/10/2014, 5:30pm
*/

#include "GLShader.h"

#include <fstream>

Shader::Shader(const std::string& file, GLenum type ) :	mType(type)
{
	
	std::ifstream fs( file.c_str(), std::ifstream::in | std::ifstream::binary );


	if(fs.good()) { 

		std::string code;
		code.assign(std::istreambuf_iterator<char>(fs), std::istreambuf_iterator<char>());

		compile(code);
	}
}

Shader::~Shader() 
{
	if(glIsShader(mShaderID))
		glDeleteShader(mShaderID);
}

void Shader::compile(const std::string& code) 
{

	// create new shader object
	mShaderID = glCreateShader(mType);
	glGetLastError();

	// upload shader code
	const GLchar* pCode = (const GLchar*)code.c_str();
	glShaderSource(mShaderID, 1, &pCode, NULL );

	// compile
	glCompileShader(mShaderID);

	// check log
	log();

	// check compile result
	glGetShaderiv( mShaderID, GL_COMPILE_STATUS, &mCompiled );

	if(!mCompiled)
		fprintf(stderr, "Failed to compile shader source code.\n");
}

void Shader::log() {

	GLint len = 0;

	glGetShaderiv(mShaderID, GL_INFO_LOG_LENGTH, &len);

	if(len > 1)
	{
		GLchar* info = new GLchar[len];
	
		glGetShaderInfoLog( mShaderID, len, NULL, info);

		fprintf(stderr, "Shader Info Log:\n%s\n", info);

		delete info;
		info = NULL;
	}
}

VertexShader::VertexShader(const std::string& file) : Shader(file, GL_VERTEX_SHADER)
{}

FragmentShader::FragmentShader(const std::string& file) : Shader(file, GL_FRAGMENT_SHADER)
{}



ShaderProgram::ShaderProgram(VertexShader* vertex_shader, FragmentShader* fragment_shader)
{
	// create new shader program
	mShaderProgramID = glCreateProgram();
	glGetLastError();

	Shader* shader[] = {

		vertex_shader,
		fragment_shader
	};

	// link program
	link(shader, 2);
}

ShaderProgram::ShaderProgram(Shader** shader, int num)
{
	// create new shader program
	mShaderProgramID = glCreateProgram();
	glGetLastError();

	link(shader, num);
}

ShaderProgram::~ShaderProgram()
{

	for(tShaderList::iterator it = mShaderList.begin(); it != mShaderList.end(); ++it) {

		delete *it;
		*it = NULL;
	}

	if(glIsProgram(mShaderProgramID))
		glDeleteProgram(mShaderProgramID);

	mShaderAttributes.clear();
	mShaderUniforms.clear();
}

void ShaderProgram::link(Shader** shader, int num)
{
	for(int i = 0; i < num; ++i) {

		// check if shader is valid
		if(shader[i]->failed()) {
		
			fprintf(stderr,"Using an invalid shader to link a program.\n");
			break;
		}

		// save shader id
		mShaderList.push_back(shader[i]);

		// attach shader to program
		glAttachShader(mShaderProgramID, shader[i]->GetShaderID());
	}

	// link program
	glLinkProgram(mShaderProgramID);

	// check log
	log();

	// get link status
	glGetProgramiv(mShaderProgramID, GL_LINK_STATUS, &mLinked);

	// validate program
	glValidateProgram(mShaderProgramID);

	if(mLinked == GL_FALSE)
		fprintf(stderr, "Failed to link shader program.\n");
}

void ShaderProgram::log() {

	GLint len = 0;

	glGetProgramiv(mShaderProgramID, GL_INFO_LOG_LENGTH, &len);

	if(len > 1)
	{
		GLchar* info = new GLchar[len];

		glGetProgramInfoLog(mShaderProgramID, len, NULL, info);

		fprintf(stderr, "Shader Program Info Log:\n%s\n", info);

		delete info;
		info = NULL;
	}
}

void ShaderProgram::Use() const
{
	glUseProgram(mShaderProgramID);
	glGetLastError();
}

void ShaderProgram::Unuse() const
{
	glUseProgram(0);
}

GLint ShaderProgram::AddAttribute(std::string& attr)
{
	GLint loc = glGetAttribLocation(this->mShaderProgramID, attr.c_str());
	glGetLastError();

	mShaderAttributes[attr] = loc;

	return loc;
}

GLint ShaderProgram::AddUniform(std::string& uni)
{
	GLint loc = glGetUniformLocation(this->mShaderProgramID, uni.c_str());
	glGetLastError();

	mShaderAttributes[uni] = loc;

	return loc;
}

GLint ShaderProgram::operator[](const std::string& attribute)
{
	tShaderVars::iterator loc = mShaderAttributes.find( attribute );

	// second chance
	if(loc == mShaderAttributes.end())
		return AddAttribute(std::string(attribute));

	return loc->second;
}

GLint ShaderProgram::operator()(const std::string& uniform)
{
	tShaderVars::iterator loc = mShaderUniforms.find( uniform );

	// second chance
	if(loc == mShaderUniforms.end())
		return AddUniform(std::string(uniform));

	return loc->second;
}