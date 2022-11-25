#include "Chunk.h"


Chunk::Chunk()
{
	Clear();
}

void Chunk::Clear()
{
	memset( m_Voxels, 0, sizeof( float ) * CHUNK_WIDTH * WORLD_HEIGHT * CHUNK_HEIGHT );
}
