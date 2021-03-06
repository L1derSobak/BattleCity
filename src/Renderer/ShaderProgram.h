#pragma once
/*
		   ╔══════════════════════════════════╗
		   ║	   CREATED BY L1derSobak      ║
		   ║   Date of creating: Aug 14, 2021 ║
		   ╚══════════════════════════════════╝
*/

#include <glad/glad.h>
#include <string>

namespace Renderer {

	class ShaderProgram
	{
	public:

		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		
		bool isCompiled() const { return m_isCompiled; }
		void use() const;
		void setInt(const std::string& name, const GLint value);

		~ShaderProgram();
	private:
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator = (const ShaderProgram&) = delete;
		ShaderProgram& operator = (ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool m_isCompiled = false;
		GLuint ID = 0;
	};

}