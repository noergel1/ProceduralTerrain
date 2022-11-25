#pragma once

#include "Vuse.h"
#include "imgui/imgui.h"
#include "imgui/imstb_rectpack.h"

#include "Terrain/Terrain.h"

using namespace Vuse;

class TerrainLayer : public Layer
{
public:
	TerrainLayer(const Camera& camera)
		:Layer("Terrain")
		,m_Terrain(camera)
		,m_NoiseData(new unsigned char[m_NoiseWidth * m_NoiseHeight])
	{
		memset( m_NoiseData, 0, m_NoiseWidth * m_NoiseHeight * sizeof(unsigned char) );
		m_Noise = new Texture_2D( m_NoiseData, m_NoiseWidth, m_NoiseHeight, ColorSpace::RED, Texture_2D::TextureSettings() );
	}

	void OnUpdate(Timestep timestep) override
	{
	}

	void OnEvent( Event& event) override
	{
		
	}

	void OnImGuiRender() override
	{

		NoiseGenerator& noiseGenerator = m_Terrain.Noise;

		GLuint textureID = m_Noise->GetID();
		ImVec2 textureSize( m_NoiseWidth, m_NoiseHeight );
		ImGui::Image( (void*)(intptr_t)textureID, textureSize );

		if (m_HasNoiseChanged)
		{
			noiseGenerator.UpdateNoise();
			GetNoiseImage();
			m_HasNoiseChanged = false;
		}
		m_HasNoiseChanged = noiseGenerator.OnImGuiRender();
		
	}

	void GetNoiseImage()
	{
		for (int i = 0; i < m_NoiseHeight; i++)
		{
			for (int j = 0; j < m_NoiseWidth; j++)
			{
				float noiseValue = m_Terrain.Noise.GetPixel( i, j );
				float noiseValueCorrected = floor((noiseValue + 1) * 256/2);
				m_NoiseData[m_NoiseWidth * i + j] = noiseValueCorrected;
			}
		}

		m_Noise->UploadImageData( 0, 0, m_NoiseWidth, m_NoiseHeight, ColorSpace::RED, m_NoiseData );
	}

private:
	Terrain m_Terrain;

	bool m_HasNoiseChanged = true;

	// noise preview image
	Texture_2D* m_Noise;
	unsigned char* m_NoiseData;
	const unsigned int m_NoiseWidth = 300;
	const unsigned int m_NoiseHeight = 300;


		
};