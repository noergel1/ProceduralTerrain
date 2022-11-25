#include "Terrain.h"

// size defines the dimensions of the terrain in chunks
Terrain::Terrain( const Vuse::Camera& camera )
	:m_Camera(camera)
	,Noise()
{
}

void Terrain::Generate()
{
	// set all chunks to 0
	m_Data.Clear();

	// create noise
	

}