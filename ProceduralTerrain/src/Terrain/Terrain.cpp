#include "Terrain.h"

#include "imgui/imgui.h"

// size defines the dimensions of the terrain in chunks
Terrain::Terrain( const Vuse::Camera& camera )
	:m_Camera(camera)
	,m_NoisePreviewData(new unsigned char[m_NoisePreviewWidth * m_NoisePreviewHeight])
{
	memset( m_NoisePreviewData, 0, m_NoisePreviewWidth * m_NoisePreviewHeight * sizeof(unsigned char) );
	m_NoisePreview = new Texture_2D( m_NoisePreviewData, m_NoisePreviewWidth, m_NoisePreviewHeight, ColorSpace::RED, Texture_2D::TextureSettings() );
}

void Terrain::Generate()
{
	// set all chunks to 0
	m_Data.Clear();

	// create noise
	

}

void Terrain::OnImGuiRender() {
	
	GLuint textureID = m_NoisePreview->GetID();
	ImVec2 textureSize( m_NoisePreviewWidth, m_NoisePreviewHeight);
	ImGui::Image( (void*)(intptr_t)textureID, textureSize );
	if(ImGui::SliderFloat( "Frequency", &m_Noise.p_Frequency, 0.001, 0.15 )) m_HasNoiseChanged = true;
	if(ImGui::SliderFloat( "Gain", &m_Noise.p_Gain , 0.001, 1.0f)) m_HasNoiseChanged = true;


	if (m_HasNoiseChanged)
	{
		m_Noise.UpdateNoise();
		GetNoiseImage();
		m_HasNoiseChanged = false;
	}		
}

void Terrain::GetNoiseImage()
	{
		for (int i = 0; i < m_NoisePreviewHeight; i++)
		{
			for (int j = 0; j < m_NoisePreviewWidth; j++)
			{
				float noiseValue = m_Noise.GetPixel( i, j );
				float noiseValueCorrected = floor((noiseValue + 1) * 256/2);
				m_NoisePreviewData[m_NoisePreviewWidth * i + j] = noiseValueCorrected;
			}
		}

		m_NoisePreview->UploadImageData( 0, 0, m_NoisePreviewWidth, m_NoisePreviewHeight, ColorSpace::RED, m_NoisePreviewData );
	}