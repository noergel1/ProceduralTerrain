#pragma once

#include "Vuse.h"

#include "World.h"
#include "TerrainSettings.h"
#include "NoiseGenerator.h"

class Terrain
{
public:
	Terrain( const Vuse::Camera& camera );

	void Generate();

	NoiseGenerator Noise;

private:
	TerrainSettings m_Settings;
	World m_Data;

	const Vuse::Camera& m_Camera;
};