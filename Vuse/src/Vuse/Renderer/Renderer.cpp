#include "vuse_pch.h"
#include "Renderer.h"

#include "RenderCommand.h"

namespace Vuse
{
	void Renderer::BeginScene()
	{

	}
	void Renderer::EndScene()
	{

	}

	void Renderer::SubmitGeometry( const std::shared_ptr<VertexArray>& vertexArray )
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed( vertexArray );
	}
}