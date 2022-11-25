#pragma once

#include "glm/glm.hpp"

#define CHUNK_WIDTH 32
#define CHUNK_HEIGHT 32
#define WORLD_HEIGHT 64

#define DEFAULT_TERRAIN_SIZE_X 1
#define DEFAULT_TERRAIN_SIZE_Y 1

class TerrainSettings
{
public:
	TerrainSettings()
		:m_WorldSize(glm::vec2(DEFAULT_TERRAIN_SIZE_X,DEFAULT_TERRAIN_SIZE_Y))
	{}

	inline void SetWorldSize( glm::vec2 size ) { m_WorldSize = size; }
	inline glm::vec2 GetWorldSize() { return m_WorldSize; }

private:
	glm::vec2 m_WorldSize;

};