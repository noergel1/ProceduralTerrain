#pragma once

#include "Vuse/Renderer/VertexLayout.h"

namespace Vuse
{

	class VertexBuffer
	{
	public:
		enum class AccessFrequency {
			STREAM,
			STATIC,
			DYNAMIC
		};

		enum class AccessType {
			DRAW,
			READ,
			COPY
		};

	public:
		VertexBuffer();
		VertexBuffer(float* vertices, uint32_t size);
		~VertexBuffer();

		void BufferData( uint32_t* _indices, uint32_t _count, AccessFrequency _accessFrequency, AccessType _accessType );
		bool BufferSubData( uint32_t* _indices, uint32_t _count, uint32_t _offset );

		void Bind() const;
		void Unbind() const;

		const BufferLayout& GetLayout() const { return m_Layout; };
		void SetLayout( const BufferLayout& layout ) { m_Layout = layout; };

		GLenum GetAccessEnum( AccessFrequency _accessFrequency, AccessType _accessType );

	private:
		uint32_t m_ID;
		BufferLayout m_Layout;

		uint32_t m_Count;
	};

	
}