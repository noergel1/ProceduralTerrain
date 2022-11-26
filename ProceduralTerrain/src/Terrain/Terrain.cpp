#include "Terrain.h"

#include "imgui/imgui.h"

// size defines the dimensions of the terrain in chunks
Terrain::Terrain( const Vuse::Camera& camera )
	:m_Camera(camera)
{
}

void Terrain::Generate()
{
	// set all chunks to 0
	m_Data.Clear();

	// create noise
	

}

void Terrain::OnUpdate() 
{
	m_Noise.OnUpdate();
}

void Terrain::OnImGuiRender() {
	m_Noise.OnImGuiRender();
	
}

