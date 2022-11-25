#include "vuse_pch.h"
#include "VertexBuffer.h"

#include <glad/glad.h>

namespace Vuse
{
	VertexBuffer::VertexBuffer( float* vertices, uint32_t size )
	{
		glCreateBuffers( 1, &m_ID );
		glBindBuffer( GL_ARRAY_BUFFER, m_ID );
		glBufferData( GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers( 1, &m_ID );
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer( GL_ARRAY_BUFFER, m_ID );
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
	}

	
}