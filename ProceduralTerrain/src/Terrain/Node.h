#pragma once

#include <memory>

struct VoxelData {
	VoxelData()
		:r(0)
		,g(0)
		,b(0)
	{ }

	VoxelData(unsigned char _r, unsigned char _g, unsigned char _b)
		:r(_r)
		,g(_g)
		,b(_b)
	{ }

	unsigned char r;
	unsigned char g;
	unsigned char b;
};

class Node
{
public:
	union NodeData
	{
		NodeData() { memset( this, 0, sizeof( NodeData ) ); }

		Node* children[8];
		VoxelData voxel[8];
	};

public:
	Node()
		:parent(nullptr)
	{ }

	Node(Node* _parent)
		:parent(_parent)
	{ }

	inline void SetChildActive( int _index ) { m_activeChildren |= s_Octants[_index]; }
	inline bool IsChildActive( int _index ) { return m_activeChildren & s_Octants[_index]; };

	// using degenerate case of node to indicate that it's a leaf node
	bool IsLeaf() { return m_activeChildren == 0; }

public:
	Node* parent;
	NodeData data;

private:
	unsigned char m_activeChildren = 0;


	static const unsigned char s_Octants[8];
};