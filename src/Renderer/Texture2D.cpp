#include "Texture2D.h"

namespace Renderer
{
	Texture2D::Texture2D(const GLuint width, const GLuint height, const unsigned char* data,
		const unsigned int channels, const GLenum filter, const GLenum wrapMode) : width(width), height(height)
	{
		switch (channels)
		{
		case 4:
			mode = GL_RGBA;
			break;
		case 3:
			mode = GL_RGB;
			break;
		default:
			mode = GL_RGBA;
			break;
		}
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, mode, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	Texture2D& Texture2D::operator = (Texture2D&& texture2d)
	{
		glDeleteTextures(1, &m_ID);
		m_ID = texture2d.m_ID;
		texture2d.m_ID = 0;
		mode = texture2d.mode;
		width = texture2d.width;
		height = texture2d.height;
		return *this;
	}

	Texture2D::Texture2D(Texture2D&& texture2d)
	{
		m_ID = texture2d.m_ID;
		texture2d.m_ID = 0;
		mode = texture2d.mode;
		width = texture2d.width;
		height = texture2d.height;
	}

	void Texture2D::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_ID);
	}

}