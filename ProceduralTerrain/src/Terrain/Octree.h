#pragma once

#include "Node.h"
#include "Chunk.h"
#include "LocationalCode.h"

#include <memory>
#include <map>
#include <set>

struct VoxelPos
{
	VoxelPos(int16_t _x, int16_t _y, int16_t _z)
		:x(_x)
		,y(_y)
		,z(_z)
	{ }

	int16_t x;
	int16_t y;
	int16_t z;
};

struct Voxel
{
	Voxel(int16_t _x, int16_t _y, int16_t _z, unsigned char _r, unsigned char _g, unsigned char _b)
		:pos(_x,_y,_z)
		,data(_r,_g,_b)
	{ }

	Voxel(VoxelPos _pos, unsigned char _r, unsigned char _g, unsigned char _b)
		:pos(_pos)
		,data(_r,_g,_b)
	{ }

	Voxel(int16_t _x, int16_t _y, int16_t _z, VoxelData _data)
		:pos(_x,_y,_z)
		,data(_data)
	{ }


	VoxelPos pos;
	VoxelData data;
};


class Octree
{

public:
	Octree( uint16_t _maxDepth );

	// sorts and inserts the voxels in queue
	void Update();

	void InsertOld( Voxel _voxel );
	void InsertNew( Voxel _voxel );
	VoxelData* GetVoxel( VoxelPos _pos );

private:
	void UpdateChunkMeshes();
	void ClearInsertQueue();

	uint32_t GetLocationalCode( int16_t _x, int16_t _y, int16_t _z );
	glm::ivec3 GetPos( uint32_t _locCode, uint16_t _depth );
	uint32_t Interleaf( uint16_t x, uint16_t y, uint16_t z );

	bool IsInBounds( VoxelPos _pos );
	uint32_t Abs_SVO( int32_t _val );

	void handleNonExistingBranch( Node** _curNode, VoxelData _data, uint16_t _curDepth, uint32_t _locCode );

private:
	Node* m_Root;

	std::set<uint32_t> m_ChangedChunks;
	std::map<uint32_t, Chunk> m_Chunks;

	std::map<uint32_t, VoxelData> m_InsertQueue;

	const uint16_t m_MaxDepth;
	const uint16_t m_MaxCoord;
};