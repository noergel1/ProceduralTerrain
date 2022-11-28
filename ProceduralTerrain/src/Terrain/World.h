 #pragma once


#include "TerrainSettings.h"
#include "Chunk.h"

#include <vector>
#include <functional>

class World
{
public:
	World();

	void SetVoxel(float value);
	float GetVoxel( glm::vec3 position ) const;

	void Clear();
	void LoopChunks( std::function<void( Chunk& )> func );

private:
	std::vector<std::vector<Chunk*>> m_Chunks;

};