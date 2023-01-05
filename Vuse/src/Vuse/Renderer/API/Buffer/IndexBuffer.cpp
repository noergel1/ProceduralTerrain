#include "vuse_pch.h"
#include "IndexBuffer.h"

#include <Vuse.h>

#include <glad/gl.h>

namespace Vuse
{
	IndexBuffer::IndexBuffer() 
		:m_Count(0)
	{
		glGenBuffers( 1, &m_ID );
	}

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

	void IndexBuffer::BufferData( uint32_t* _indices, uint32_t _count, AccessFrequency _accessFrequency, AccessType _accessType ) {
		Bind();
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( uint32_t ) * _count, _indices, GetAccessEnum(_accessFrequency, _accessType) );
	}

	bool IndexBuffer::BufferSubData( uint32_t* _indices, uint32_t _count, uint32_t _offset ) {
		Bind();
		if (_count <= m_Count) {
			glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, _offset, sizeof( uint32_t ) * _count, _indices );
			return true;
		}
		else {
			VUSE_CORE_WARN( "IndexBuffer::BufferSubData : Indices too big for currently allocated memory! (${0}/${1})\n", _count, m_Count );
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( uint32_t ) * _count, _indices, GetAccessEnum(AccessFrequency::DYNAMIC, AccessType::DRAW) );
			return false;
		}
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ID );
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	}

	GLenum IndexBuffer::GetAccessEnum( AccessFrequency _accessFrequency, AccessType _accessType ) {
		switch (_accessFrequency) {
			case AccessFrequency::STATIC:
			{
				switch (_accessType) {
					case(AccessType::DRAW): return GL_STATIC_DRAW;
					case(AccessType::READ): return GL_STATIC_READ;
					case(AccessType::COPY): return GL_STATIC_COPY;
				}
			}
			case AccessFrequency::DYNAMIC:
			{
				switch (_accessType) {
					case(AccessType::DRAW): return GL_DYNAMIC_DRAW;
					case(AccessType::READ): return GL_DYNAMIC_READ;
					case(AccessType::COPY): return GL_DYNAMIC_COPY;
				}
			}
			case AccessFrequency::STREAM:
			{
				switch (_accessType) {
					case(AccessType::DRAW): return GL_STREAM_DRAW;
					case(AccessType::READ): return GL_STREAM_READ;
					case(AccessType::COPY): return GL_STREAM_COPY;
				}
			}
		}
	}
}