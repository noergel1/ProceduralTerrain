#include "Octree.h"

#include <iostream>
#include <bitset>

Octree::Octree( uint16_t _maxDepth )
	:m_MaxDepth(_maxDepth)
	,m_MaxCoord(pow(2, _maxDepth-1))
	,m_Root(new Node())
{
	if (_maxDepth < Chunk::s_ChunkDepth) VUSE_ASSERT( "Octree max depth needs to be >= chunk depth(${0})!", Chunk::s_ChunkDepth );
}

void Octree::Update() {
	
}

void Octree::InsertOld( Voxel _voxel )
{
	VoxelPos& pos = _voxel.pos;

	// check if voxel is inside octree boundaries, if not skip
	if (!IsInBounds( pos ))
	{
		VUSE_TRACE( "Voxel (${0},${1},${2}) not in bounds!\n", pos.x, pos.y, pos.z );
		return;
	}

	// get loc code for traveral
	uint32_t loc_code = GetLocationalCode( pos.x, pos.y, pos.z );

	// traverse the tree
	/////////////////////
	Node* curNode = m_Root;
	for(int curDepth = 0; curDepth < m_MaxDepth-1; curDepth++)
	{
		unsigned char nextIndex = (loc_code >> (3*curDepth)) & 0b111;

		// if branch doesn't exist, create new one
		if (!curNode->IsChildActive( nextIndex )) {
			// different codepath since all following branches are also empty
			handleNonExistingBranch( &curNode, _voxel.data, curDepth, loc_code );
			break;
		}

		curNode = curNode->data.children[nextIndex];
	}

	// if we reach max depth, insert the data
	unsigned char nextIndex = loc_code >> ((m_MaxDepth-1) * 3);
	curNode->data.voxel[nextIndex].r = _voxel.data.r;
	curNode->data.voxel[nextIndex].g = _voxel.data.g;
	curNode->data.voxel[nextIndex].b = _voxel.data.b;
	curNode->SetChildActive( nextIndex );
}


void Octree::InsertNew( Voxel _voxel )
{
	VoxelPos& pos = _voxel.pos;

	// check if voxel is inside octree boundaries, if not skip
	if (!IsInBounds( pos ))
	{
		printf( "Voxel (%i,%i,%i) not in bounds!\n", pos.x, pos.y, pos.z );
		return;
	}

	// get loc code for traveral
	uint32_t loc_code = GetLocationalCode( pos.x, pos.y, pos.z );

	// add to insertion map
	m_InsertQueue[loc_code] = _voxel.data;
}

VoxelData* Octree::GetVoxel( VoxelPos _pos )
{
	// check if voxel is inside octree boundaries, if not skip
	if (!IsInBounds( _pos ))
	{
		printf( "Voxel (%i,%i,%i) not in bounds!\n", _pos.x, _pos.y, _pos.z );
		return nullptr;
	}

	Node* curNode = m_Root;

	// get loc code for traveral
	uint32_t loc_code = GetLocationalCode( _pos.x, _pos.y, _pos.z );

	// traverse the tree
	/////////////////////
	for(int curDepth = 0; curDepth < m_MaxDepth-1; curDepth++)
	{
		unsigned char nextIndex = (loc_code >> (3*curDepth)) & 0b111;

		// if branch doesn't exist, create new one
		if (!curNode->IsChildActive( nextIndex )) {
			return nullptr;
		}

		curNode = curNode->data.children[nextIndex];
	}
	
	// if we reach max depth, check if voxel is set
	unsigned char nextIndex = (loc_code >> (3*(m_MaxDepth-1))) & 0b111;
	if (curNode->IsChildActive( nextIndex )) return &curNode->data.voxel[nextIndex];
	else return nullptr;
}

void Octree::UpdateChunkMeshes() {

	for (auto curLocCode : m_ChangedChunks) {
		m_Chunks[curLocCode].Update();
		m_ChangedChunks.erase( curLocCode );
	}
}

void Octree::ClearInsertQueue() {
	// since maps are sorted we can avoid going from the root to the insertion point for every voxel
	// instead we look for the first difference in the location code from MSB to LSB
	// 
	// this should save a lot of time, since usually we either will a big part of the octree at once
	// or insert multiple voxels in close proximity

	Node* curNode = m_Root;
	uint16_t curDepth = 0;
	uint32_t lastLocCode = 0;

	for (std::map<uint32_t, VoxelData>::const_iterator it = m_InsertQueue.begin(); it != m_InsertQueue.end(); ++it)
	{
		uint32_t locCode = it->first;
		VoxelData data = it->second;

		if (it == m_InsertQueue.begin()) lastLocCode = ~locCode;

		unsigned char firstDifference = m_MaxDepth-1;
		for (int i = 0; i <= (m_MaxDepth-1); i++)
		{
			static const unsigned char bitmask = 0b111;
			
			if (((locCode >> (3 * i)) & bitmask) == ((lastLocCode >> (3 * i)) & bitmask))
			{
				continue;
			}
			else
			{
				firstDifference = i;
				break;
			};
		}


		while (curDepth > firstDifference)
		{
			curNode = curNode->parent;
			curDepth--;
		}

		// traverse the tree
		/////////////////////
		for(curDepth; curDepth < m_MaxDepth-1; curDepth++)
		{
			unsigned char nextIndex = (locCode >> (3*curDepth)) & 0b111;

			// if branch doesn't exist, create new one
			if (!curNode->IsChildActive( nextIndex )) {
				// different codepath since all following branches are also empty
				handleNonExistingBranch( &curNode, data, curDepth, locCode );
				curDepth = m_MaxDepth-1;
				break;
			}

			curNode = curNode->data.children[nextIndex];
		}

		// flag chunk as changed to regenerate mesh
		m_ChangedChunks.insert( locCode >> (3 * Chunk::s_ChunkDepth) );

		// if we reach max depth, insert the data
		unsigned char nextIndex = locCode >> ((m_MaxDepth-1) * 3);
		curNode->data.voxel[nextIndex].r = data.r;
		curNode->data.voxel[nextIndex].g = data.g;
		curNode->data.voxel[nextIndex].b = data.b;
		curNode->SetChildActive( nextIndex );

		lastLocCode = locCode;
	}
}

uint32_t Octree::GetLocationalCode( int16_t _x, int16_t _y, int16_t _z )
{
	// normalize to svo coords
	uint32_t norm_x = _x + m_MaxCoord;
	uint32_t norm_y = _y + m_MaxCoord;
	uint32_t norm_z = _z + m_MaxCoord;

	//generate locational code
	return Interleaf( norm_x, norm_y, norm_z );
}

glm::ivec3 Octree::GetPos( uint32_t _locCode, uint16_t _depth ) {
	uint32_t x = 0;
	uint32_t y = 0;
	uint32_t z = 0;

	for (int i = 0; i < m_MaxDepth; i++) {
		unsigned char curIndex = (_locCode >> (3 * i)) && 0b111;

		z |= curIndex & 0b1;
		y |= (curIndex >> 1) & 0b1;
		z |= (curIndex >> 2) & 0b1;

		z <<= 1;
		y <<= 1;
		x <<= 1;
	}

	z >>= 1;
	y >>= 1;
	x >>= 1;


	return glm::ivec3(
		x - m_MaxCoord,
		y - m_MaxCoord,
		z - m_MaxCoord
	);
}

uint32_t Octree::Interleaf( uint16_t x, uint16_t y, uint16_t z ) {
	uint32_t code = 0;
	for (int i = 0; i < m_MaxDepth; i++) {
		code |= (x & 1);
		code <<= 1;
		code |= (y & 1);
		code <<= 1;
		code |= (z & 1);
		code <<= 1;
		x >>= 1;
		y >>= 1;
		z >>= 1;
	}
	return code>>1;
}

bool Octree::IsInBounds( VoxelPos _pos )
{
    return !((Abs_SVO(_pos.x) | Abs_SVO(_pos.y) | Abs_SVO(_pos.z)) >= m_MaxCoord);
}

uint32_t Octree::Abs_SVO( int32_t _val )
{
    return _val < 0 ? (-_val -1) : _val;
}

void Octree::handleNonExistingBranch( Node** _curNode, VoxelData _data, uint16_t _curDepth, uint32_t _locCode ) {
	uint16_t chunkDepth = m_MaxDepth - Chunk::s_ChunkDepth;
	for (int i = _curDepth; i < m_MaxDepth-1; i++) {
		unsigned char nextIndex = (_locCode >> (3 * i)) & 0b111;
		Node* newNode = new Node( *_curNode );

		// also check if we are at chunk depth
		// if yes, create the chunk in map
		if (_curDepth == chunkDepth) {
			m_Chunks[_locCode >> (3 * Chunk::s_ChunkDepth)] = Chunk( newNode );
		}

		(* _curNode)->SetChildActive(nextIndex);
		(* _curNode)->data.children[nextIndex] = newNode;
		(* _curNode) = newNode;
	}
}
