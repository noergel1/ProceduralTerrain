#include "vuse_pch.h"

#include "Texture_2D.h"
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


namespace Vuse
{
	Texture_2D::Texture_2D(const char* filepath, TextureSettings settings)
		:Texture( TextureType::Texture2D )
		,m_Width(0)
		,m_Height(0)
		{
		Bind();

		int nrChannels, width, height;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);

		if (data)
		{
			GLenum colorMode;
			switch (nrChannels) {
				case 1:
					colorMode = GL_RED;
					break;
				case 3:
					colorMode = GL_RGB;
					break;
				case 4:
					colorMode = GL_RGBA;
					break;
				default: 
					VUSE_CORE_WARN("Unexpected texture nrChannels: {0} for {1}",nrChannels, filepath);
					colorMode = GL_RGB;
			};

			m_Width = width;
			m_Height = height;

			glTexImage2D(m_TextureType, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data);
			
			SetTextureFilter( settings.filterMin, settings.filterMag );
			SetWrap( settings.wrapS, settings.wrapT );
			GenerateMipmaps();
		}
		else
		{
			VUSE_CORE_ERROR("Failed to load texture {0}", filepath);
		}

		stbi_image_free(data);
		Unbind();
	}

	Texture_2D::Texture_2D( unsigned char* data, unsigned int width, unsigned int height, ColorSpace colorSpace, TextureSettings settings )
		:Texture(TextureType::Texture2D)
		,m_Width(width)
		,m_Height(height)
	{
		glBindTexture( m_TextureType, m_ID );

		GLenum colorSpace_gl = ColorSpaceToGLenum( colorSpace );

		glTexImage2D( m_TextureType, 0, colorSpace_gl, m_Width, m_Height, 0, colorSpace_gl, GL_UNSIGNED_BYTE, data );

		SetTextureFilter( settings.filterMin, settings.filterMag );
		SetWrap( settings.wrapS, settings.wrapT );
		GenerateMipmaps();

		Unbind();
	}

	void Texture_2D::UploadImageData( unsigned int xOffset, unsigned int yOffset, unsigned int width, unsigned int height, ColorSpace colorSpace, unsigned char* data )
	{
		Bind();
		glTexSubImage2D(
			m_TextureType, 0, xOffset, yOffset, width, height, ColorSpaceToGLenum( colorSpace ), GL_UNSIGNED_BYTE, data );
		Unbind();
	}

	void Texture_2D::SetWrap( TextureWrap s, TextureWrap t )
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapToGLenum(s));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapToGLenum(t));
	}
}