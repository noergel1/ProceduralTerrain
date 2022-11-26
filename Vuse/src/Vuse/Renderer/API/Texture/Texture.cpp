#include "vuse_pch.h"

#include "Texture.h"

#include <glad/gl.h>

namespace Vuse
{

	Texture::Texture( TextureType textureType )
		:m_TextureType(TextureTypeToGLenum(textureType))
	{
		glGenTextures( 1, &m_ID );
	}

	Texture::~Texture()
	{
		glDeleteTextures( 1, &m_ID );
	}

	GLuint Texture::GetID() const
	{
		return m_ID;
	};

	void Texture::Bind()
	{
		glBindTexture( m_TextureType, m_ID );
	}

	void Texture::Unbind()
	{
		glBindTexture(m_TextureType, m_ID);
	}

	void Texture::SetActiveTextureSlot( unsigned int textureSlot )
	{
		s_ActiveTextureSlot = textureSlot;
		glActiveTexture( GL_TEXTURE0 + textureSlot );
	}

	unsigned int Texture::GetActiveTextureSlot()
	{
		return s_ActiveTextureSlot;
	}

	void Texture::SetTextureFilter( TextureFilterMin min, TextureFilterMag mag )
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilterMinToGLenum(min));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilterMagToGLenum(mag));
	}

	void Texture::GenerateMipmaps()
	{
		Bind();
		glGenerateMipmap(m_TextureType);
	};


	GLenum Texture::TextureTypeToGLenum( TextureType textureType )
	{
		switch (textureType)
		{
			case(TextureType::Texture2D): return GL_TEXTURE_2D;
			case(TextureType::Texture3D): return GL_TEXTURE_3D;
			case(TextureType::Cubemap): return GL_TEXTURE_CUBE_MAP;
		}
	}

	GLenum Texture::TextureFilterMagToGLenum( TextureFilterMag textureFilter )
	{
		switch (textureFilter)
		{
			case(TextureFilterMag::Linear): return GL_LINEAR;
			case(TextureFilterMag::Nearest): return GL_NEAREST;
		}
	}
	
	GLenum Texture::TextureFilterMinToGLenum( TextureFilterMin textureFilter )
	{
		switch (textureFilter)
		{
			case(TextureFilterMin::Linear): return GL_LINEAR;
			case(TextureFilterMin::Nearest): return GL_NEAREST;
			case(TextureFilterMin::Nearest_Mipmap_Nearest): return GL_NEAREST_MIPMAP_NEAREST;
			case(TextureFilterMin::Nearest_Mipmap_Linear): return GL_NEAREST_MIPMAP_LINEAR;
			case(TextureFilterMin::Linear_Mipmap_Nearest): return GL_LINEAR_MIPMAP_NEAREST;
			case(TextureFilterMin::Linear_Mipmap_Linear): return GL_LINEAR_MIPMAP_LINEAR;
		}
	}

	GLenum Texture::TextureWrapToGLenum( TextureWrap textureWrap )
	{
		switch (textureWrap)
		{
			case(TextureWrap::Repeat): return GL_REPEAT;
			case(TextureWrap::Mirrored_Repeat): return GL_MIRRORED_REPEAT;
			case(TextureWrap::Clamp_To_Border): return GL_CLAMP_TO_BORDER;
			case(TextureWrap::Clamp_To_Edge): return GL_CLAMP_TO_EDGE;
		}
	}

	GLenum Texture::ColorSpaceToGLenum( ColorSpace colorSpace )
	{
		switch (colorSpace)
		{
			case(ColorSpace::RED): return GL_RED;
			case(ColorSpace::RGB): return GL_RGB;
			case(ColorSpace::RGBA): return GL_RGBA;
		}
	}
}