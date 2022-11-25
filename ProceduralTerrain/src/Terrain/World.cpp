#include "World.h"

World::World()
{

}

void World::SetVoxel(float value)
{

}

float World::GetVoxel( glm::vec3 position ) const
{
	return 1.0f;
}

void World::Clear()
{
	LoopChunks( [this]( Chunk& chunk ) {
		chunk.Clear();
		} );
}

void World::LoopChunks(std::function<void (Chunk&)> func)
{
	for (int i = 0; i < m_Chunks.size(); i++)
	{
		for (int j = 0; j < m_Chunks[i].size(); j++)
		{
			func( *m_Chunks[i][j] );
		}
	}
}
