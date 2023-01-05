#pragma once

#include "Vuse.h"
#include "Node.h"

#include <memory>

using namespace Vuse;

class Chunk {
public:
	Chunk(Node* _node) 
		:m_Node(_node)
		,m_VAO()
		,m_VBO()
		,m_EBO()
		,m_IsGenerated(false)
	{
		Update();
	}

	void Update();

	std::vector<std::vector<uint16_t>>* GetVoxels();
	void Iterate( std::vector<std::vector<uint16_t>>* _voxels, Node* _node, uint16_t _curDepth, uint32_t _curLocCode );

public:
	static const uint16_t s_ChunkDepth = 5;
	static const uint32_t s_DefaultMemAllocationSize = 200;

private:
	Node* m_Node;
	VertexArray m_VAO;
	IndexBuffer m_EBO;
	VertexBuffer m_VBO;

	uint32_t* m_VerticeBuffer;
	uint16_t m_IndiceCount;

	bool m_IsGenerated;

};