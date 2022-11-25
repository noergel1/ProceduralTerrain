#pragma once

#include "RenderCommand.h"

namespace Vuse
{

	class Renderer
	{
	public:
		static void BeginScene(); // TODO take in scene parameters
		static void EndScene();

		static void SubmitGeometry( const std::shared_ptr<VertexArray>& vertexArray );
	};
}