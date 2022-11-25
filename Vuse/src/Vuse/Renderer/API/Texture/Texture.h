#pragma once

	typedef unsigned int GLenum;
	typedef unsigned int GLuint;
namespace Vuse
{

	enum class TextureType
	{
		Texture2D,
		Texture3D,
		Cubemap
	};

	enum class TextureFilterMag
	{
		Linear,
		Nearest
	};

	enum class TextureWrap
	{
		Repeat,
		Mirrored_Repeat,
		Clamp_To_Edge,
		Clamp_To_Border
	};

	enum class TextureFilterMin
	{		
		Linear,
		Nearest,
		Nearest_Mipmap_Nearest,
		Linear_Mipmap_Nearest,
		Nearest_Mipmap_Linear,
		Linear_Mipmap_Linear
	};

	enum class ColorSpace
	{
		RED,
		RGB,
		RGBA
	};

	class Texture
	{
	public:
		Texture( TextureType textureType );
		~Texture();

		GLuint GetID() const;

		void Bind();
		void Unbind();

		static void SetActiveTextureSlot( unsigned int textureSlot );
		static unsigned int GetActiveTextureSlot();

		void SetTextureFilter(TextureFilterMin min, TextureFilterMag mag);

		void GenerateMipmaps();

	protected:
		static GLenum TextureTypeToGLenum( TextureType textureType );
		static GLenum TextureFilterMagToGLenum( TextureFilterMag textureFilter );
		static GLenum TextureFilterMinToGLenum( TextureFilterMin textureFilter );
		static GLenum TextureWrapToGLenum( TextureWrap textureWrap );
		static GLenum ColorSpaceToGLenum( ColorSpace colorSpace );

	protected:
		GLuint m_ID;
		const GLenum m_TextureType;

	private:
		inline static unsigned int s_ActiveTextureSlot = 0;
	};
}