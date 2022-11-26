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

	void OnImGuiRender();
	
	void GetNoiseImage();

private:
	NoiseGenerator m_Noise;
	TerrainSettings m_Settings;
	World m_Data;

	// noise preview image
	bool m_HasNoiseChanged = true;
	Texture_2D* m_NoisePreview;
	unsigned char* m_NoisePreviewData;
	const unsigned int m_NoisePreviewWidth = 300;
	const unsigned int m_NoisePreviewHeight = 300;


	const Vuse::Camera& m_Camera;
};