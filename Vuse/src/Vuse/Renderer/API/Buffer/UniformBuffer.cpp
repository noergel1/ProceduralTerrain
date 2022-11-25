#include "vuse_pch.h"
#include "UniformBuffer.h"

namespace Vuse
{
	UniformBuffer::UniformBuffer( uint32_t index, const std::initializer_list<BufferElement>& elements )
		:m_Index(index)
	{
		glGenBuffers( 1, &m_ID );
		glBindBuffer( GL_UNIFORM_BUFFER, m_ID );
		glBufferData( GL_UNIFORM_BUFFER, 4*16, NULL, GL_STATIC_DRAW);
		glBindBufferRange( GL_UNIFORM_BUFFER, m_Index, m_ID, 0, 4 * sizeof( glm::vec4 ) );
		glBindBuffer( GL_UNIFORM_BUFFER, 0 );
	}
}