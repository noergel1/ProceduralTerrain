#pragma once

namespace Vuse
{
	class IndexBuffer
	{
	public:
		IndexBuffer( uint32_t* indices, uint32_t count );
		~IndexBuffer();

		void Bind();
		void Unbind();

		inline const uint32_t GetCount() const { return m_Count; };

	private:
		uint32_t m_ID;

		uint32_t m_Count;
	};
}