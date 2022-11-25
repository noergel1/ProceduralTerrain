#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

#include "Vuse/Renderer/VertexLayout.h"

namespace Vuse
{
	class Std140_Layout
	{

	};


	class UniformBuffer
	{
	public:
		UniformBuffer( uint32_t index, const std::initializer_list<BufferElement>& elements );


	private:
		uint32_t m_ID;
		uint32_t m_Index;

	};
}