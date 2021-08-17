/*
		   ╔══════════════════════════════════╗
		   ║	   CREATED BY L1derSobak      ║
		   ║   Date of creating: Aug 14, 2021 ║
		   ╚══════════════════════════════════╝
*/


#include "ShaderProgram.h"
#include <iostream>

namespace Renderer
{

	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
	{
		GLuint vertexShaderID;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
		{
			std::cerr << "VERTEX SHADER compile-time error\n";
			glDeleteShader(vertexShaderID);
			return;
		}

		GLuint fragmentShaderID;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			std::cerr << "FRAGMENT SHADER compile-time error\n";
			glDeleteShader(vertexShaderID);
			glDeleteShader(fragmentShaderID);
			return;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertexShaderID);
		glAttachShader(ID, fragmentShaderID);
		glLinkProgram(ID);

		GLint success;
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar infolog[1024];
			glGetShaderInfoLog(ID, 1024, nullptr, infolog);
			std::cerr << "ERROR::SHADER: Link-time error:\n" << infolog << std::endl;
			return;
		}
		else
		{
			m_isCompiled = true;
		}

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		const GLchar* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infolog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infolog);
			std::cerr << "ERROR::SHADER: Compile-time error:\n" << infolog << std::endl;
			return false;
		}
		return true;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(ID);
	}

	void ShaderProgram::use() const
	{
		glUseProgram(ID);
	}

	ShaderProgram& ShaderProgram::operator = (ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(ID);
		ID = shaderProgram.ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.ID = 0;
		shaderProgram.m_isCompiled = false;
		
		return *this;
	}

	ShaderProgram::ShaderProgram (ShaderProgram&& shaderProgram) noexcept
	{
		ID = shaderProgram.ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.ID = 0;
		shaderProgram.m_isCompiled = false;
	}
}   