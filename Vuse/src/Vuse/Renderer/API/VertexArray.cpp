#include "vuse_pch.h"
#include "VertexArray.h"

#include <glad/gl.h>

namespace Vuse
{

	GLenum ShaderDataTypeToOpenGLBaseType( ShaderDataType type )
	{
		switch (type)
		{
			case(ShaderDataType::Bool):		return GL_BOOL;
			case(ShaderDataType::Int ):		return GL_INT;
			case(ShaderDataType::Int2 ):	return GL_INT;
			case(ShaderDataType::Int3 ):	return GL_INT;
			case(ShaderDataType::Int4):		return GL_INT;
			case(ShaderDataType::Float ):	return GL_FLOAT;
			case(ShaderDataType::Float2 ):	return GL_FLOAT;
			case(ShaderDataType::Float3 ):	return GL_FLOAT;
			case(ShaderDataType::Float4):	return GL_FLOAT;
			case(ShaderDataType::Mat3 ):	return GL_FLOAT;
			case(ShaderDataType::Mat4):		return GL_FLOAT;
		}

		VUSE_CORE_ASSERT( false, "Unknown ShaderDataType!" );
		return 0;
	}

	VertexArray::VertexArray()
	{
		glGenVertexArrays( 1, &m_ID );
	}

	VertexArray::~VertexArray() 
	{
		glDeleteVertexArrays( 1, &m_ID );
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray( m_ID );
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray( 0 );
	}

	void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer )
	{
		VUSE_CORE_ASSERT( vertexBuffer->GetLayout().GetElements().size(), "VertexBuffer has no layout!" );

		glBindVertexArray( m_ID );
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray( index );
			glVertexAttribPointer( 
				index, 
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType( element.Type ),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(), 
				(const void*)element.Offset 
			);
			index++;
		}
		m_VertexBuffers.push_back( vertexBuffer );
		glBindVertexArray( 0 );
	}

	void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer )
	{
		glBindVertexArray( m_ID );
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
		glBindVertexArray( 0 );
	}

	const std::vector<std::shared_ptr<VertexBuffer>>& VertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}

	const std::shared_ptr<IndexBuffer>& VertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}
}