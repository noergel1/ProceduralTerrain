#include "vuse_pch.h"
#include "IndexBuffer.h"

#include <glad/gl.h>

namespace Vuse
{
	IndexBuffer::IndexBuffer( uint32_t* indices, uint32_t count )
		:m_Count(count)
	{
		glGenBuffers( 1, &m_ID );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ID );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( uint32_t ) * count, indices, GL_STATIC_DRAW );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers( 1, &m_ID );
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ID );
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	}
}