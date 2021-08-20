#pragma once

/*
		   ╔══════════════════════════════════╗
		   ║	   CREATED BY L1derSobak      ║
		   ║   Date of creating: Aug 16, 2021 ║
		   ╚══════════════════════════════════╝
*/


#include <glad/glad.h>
#include <string>

namespace Renderer
{
	class Texture2D
	{
	public:
		Texture2D(const GLuint width, const GLuint hight, const unsigned char* data, const unsigned int channels = 4, 
					const GLenum filter = GL_LINEAR, const GLenum wrapMode = GL_CLAMP_TO_EDGE);	

		void bind() const;

		~Texture2D();
	private:
		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator = (const Texture2D&) = delete;

		Texture2D& operator = (Texture2D&& texture2d);
		Texture2D(Texture2D&& texture2d);

		GLuint ID;
		GLenum mode;
		GLuint width;
		GLuint height;
	};



}