#include "vuse_pch.h"
#include "RenderCommand.h"

#include <glad/glad.h>

namespace Vuse
{
	void RenderCommand::SetClearColor( const glm::vec4& color )
	{
		glClearColor( color.r, color.g, color.b, color.a );
	}

	void RenderCommand::Clear() 
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderCommand::EnableFaceCulling( bool enable )
	{
		if (enable)
		{
			glEnable( GL_CULL_FACE );
			return;
		}
		else
		{
			glDisable( GL_CULL_FACE );
		}
	}

	void RenderCommand::SetFrontFace( FrontFace frontFace )
	{
		GLenum frontFace_gl;
		switch (frontFace)
		{
			case FrontFace::CLOCKWISE:
			{
				frontFace_gl = GL_CW;
				break;
			}
			case FrontFace::COUNTERCLOCKWISE:
			{
				frontFace_gl = GL_CCW;
				break;
			}
		}
		glFrontFace( frontFace_gl );
	}

	void RenderCommand::SetCullFace( CullFaces cullFace )
	{
		GLenum cullFaces_gl;
		switch (cullFace)
		{
			case CullFaces::FRONT:
			{
				cullFaces_gl = GL_FRONT;
				break;
			}
			case CullFaces::BACK:
			{
				cullFaces_gl = GL_BACK;
				break;
			}
			case CullFaces::FRONT_AND_BACK:
			{
				cullFaces_gl = GL_FRONT_AND_BACK;
				break;
			}
		}
		glCullFace( cullFaces_gl );
	}

	void RenderCommand::DrawIndexed( const std::shared_ptr<VertexArray>& vertexArray ) 
	{
		glDrawElements( GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr );
	}
}