#pragma once

#include "Vuse.h"

#include "World.h"
#include "TerrainSettings.h"
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
	TerrainSettings m_Settings;
	World m_Data;



	const Vuse::Camera& m_Camera;
};