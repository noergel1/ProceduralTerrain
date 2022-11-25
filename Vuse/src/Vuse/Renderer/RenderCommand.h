#pragma once
#include "Vuse/Renderer/API/VertexArray.h"

#include <glm/glm.hpp>


namespace Vuse
{
	enum class CullFaces
	{
		FRONT,
		BACK,
		FRONT_AND_BACK
	};

	enum class FrontFace
	{
		CLOCKWISE,
		COUNTERCLOCKWISE
	};

	class RenderCommand
	{
	public:
		static void SetClearColor( const glm::vec4& color );
		static void Clear();

		static void EnableFaceCulling( bool enable );
		static void SetFrontFace( FrontFace frontFace );
		static void SetCullFace( CullFaces cullFace );

		static void DrawIndexed( const std::shared_ptr<VertexArray>& vertexArray );
	};
}