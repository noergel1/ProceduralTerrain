#pragma once

#include "Texture.h"

namespace Vuse
{
	class Texture_2D : public Texture
	{
	public:
		struct TextureSettings
		{
			TextureWrap wrapS = TextureWrap::Repeat;
			TextureWrap wrapT = TextureWrap::Repeat;
			TextureFilterMin filterMin = TextureFilterMin::Nearest;
			TextureFilterMag filterMag = TextureFilterMag::Nearest;
		};

	public:
		Texture_2D( const char* filepath, TextureSettings settings );
		Texture_2D( unsigned char* data, unsigned int width, unsigned int height, ColorSpace colorSpace, TextureSettings settings );

		void UploadImageData( unsigned int xOffset, unsigned int yOffset, unsigned int width, unsigned int height, ColorSpace colorSpace, unsigned char* data );

		void SetWrap( TextureWrap s, TextureWrap t );

		inline unsigned int GetWidth() { return m_Width; }
		inline unsigned int GetHeight() { return m_Height; }

	private:
		int m_Width;
		int m_Height;
	};
}