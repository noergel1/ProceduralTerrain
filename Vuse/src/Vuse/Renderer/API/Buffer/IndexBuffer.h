#pragma once

namespace Vuse
{
	class IndexBuffer
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
		IndexBuffer();
		IndexBuffer( uint32_t* indices, uint32_t count );
		~IndexBuffer();

		void BufferData( uint32_t* _indices, uint32_t _count, AccessFrequency _accessFrequency, AccessType _accessType );
		bool BufferSubData( uint32_t* _indices, uint32_t _count, uint32_t _offset );

		void Bind();
		void Unbind();

		inline const uint32_t GetCount() const { return m_Count; };

	private:
		GLenum GetAccessEnum( AccessFrequency _accessFrequency, AccessType _accessType );

	private:
		uint32_t m_ID;

		uint32_t m_Count;
	};
}