#pragma once

#include "TerrainSettings.h"

class Chunk
{
public:
	Chunk();

	void Clear();

private:
	float m_Voxels[CHUNK_WIDTH][WORLD_HEIGHT][CHUNK_HEIGHT];
};