#pragma once

#include "Vuse.h"

#include "Octree.h"
#include "NoiseGenerator.h"

using namespace Vuse;

class Terrain
{
public:
	Terrain( const Vuse::Camera& camera );

	void Generate();

	void OnUpdate();
	void OnImGuiRender();
	
	void GetNoisePreview();

private:
	NoiseGenerator m_Noise;
	Octree m_World;




	const Vuse::Camera& m_Camera;
};