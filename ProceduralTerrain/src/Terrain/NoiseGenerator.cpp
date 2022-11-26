#include "NoiseGenerator.h"

#include <imgui/imgui.h>

NoiseGenerator::NoiseGenerator()
	:m_NoisePreviewData(new unsigned char[m_NoisePreviewWidth * m_NoisePreviewHeight])
{
	memset( m_NoisePreviewData, 0, m_NoisePreviewWidth * m_NoisePreviewHeight * sizeof(unsigned char) );
	m_NoisePreview = new Texture_2D( m_NoisePreviewData, m_NoisePreviewWidth, m_NoisePreviewHeight, ColorSpace::RED, Texture_2D::TextureSettings() );

	p_NoiseType = NoiseType::OpenSimplex2;
	p_RotationType = RotationType::None;
	p_Seed = 1550;
	p_Frequency = 0.01;
	p_FractalType = FractalType::FBm;
	p_Octaves = 5;
	p_Lacunarity = 2.0f;
	p_FractalGain = 0.5f;
	p_WeightedStrength = 0.0f;
	p_PingPongStrength = 2.0f;
	p_DomainWarpEnabled = false;
	p_DomainWarpType = DomainWarpType::OpenSimplex2;
	p_DomainWarpAmplitude = 30.0f;
}

float NoiseGenerator::GetPixel( float x, float y )
{
	if (p_DomainWarpEnabled) m_FastNoiseLite.DomainWarp( x, y );
	return m_FastNoiseLite.GetNoise( x, y );
}

float NoiseGenerator::GetPixel( float x, float y, float z )
{
	return m_FastNoiseLite.GetNoise( x, y, z );
}

void NoiseGenerator::UpdateNoiseSettings()
{
	SetSeed( p_Seed );
	SetFrequency( p_Frequency );
	SetNoiseType( p_NoiseType );
	SetFractalType( p_FractalType );
	SetOctaves( p_Octaves );
	SetLacunarity( p_Lacunarity );
	SetFractalGain( p_FractalGain );
	SetWeightedStrength( p_WeightedStrength );
	SetPingPongEffectStrength( p_PingPongStrength );
}

void NoiseGenerator::UpdateNoisePreview()
{
	for (int i = 0; i < m_NoisePreviewHeight; i++)
	{
		for (int j = 0; j < m_NoisePreviewWidth; j++)
		{
			float noiseValue = GetPixel( i, j );
			float noiseValueCorrected = floor((noiseValue + 1) * 256/2);
			m_NoisePreviewData[m_NoisePreviewWidth * i + j] = noiseValueCorrected;
		}
	}

	m_NoisePreview->UploadImageData( 0, 0, m_NoisePreviewWidth, m_NoisePreviewHeight, ColorSpace::RED, m_NoisePreviewData );
}

void NoiseGenerator::OnUpdate() 
{
	if (m_HasNoiseChanged)
	{
		UpdateNoiseSettings();
		UpdateNoisePreview();
		m_HasNoiseChanged = false;
	}	
}

void NoiseGenerator::OnImGuiRender() {
	ImVec2 Padding( 0.0f, 10.0f );

	GLuint textureID = m_NoisePreview->GetID();
	ImVec2 textureSize( m_NoisePreviewWidth, m_NoisePreviewHeight);
	ImGui::Image( (void*)(intptr_t)textureID, textureSize );

	// General
	/////////////
	ImGui::Dummy( Padding );
	ImGui::Text( "General" );
	if (ImGui::SliderInt( "Seed", &p_Seed, 0, 2000 )) m_HasNoiseChanged = true;
	if (ImGui::SliderFloat( "Frequency", &p_Frequency, 0.001, 0.15 )) m_HasNoiseChanged = true;

	std::string SelectedNoiseTypeLabel = NoiseTypeToString(p_NoiseType);
	if (ImGui::BeginCombo( "NoiseType", SelectedNoiseTypeLabel.c_str()  ))
	{
		if(ImGui::Selectable( NoiseTypeToString(NoiseType::OpenSimplex2).c_str(), false)) p_NoiseType = NoiseType::OpenSimplex2;
		if(ImGui::Selectable( NoiseTypeToString( NoiseType::OpenSimplex2S ).c_str(), false)) p_NoiseType = NoiseType::OpenSimplex2S;
		if(ImGui::Selectable( NoiseTypeToString( NoiseType::Perlin ).c_str(), false)) p_NoiseType = NoiseType::Perlin;
		if(ImGui::Selectable( NoiseTypeToString( NoiseType::Value ).c_str(), false)) p_NoiseType = NoiseType::Value;
		if(ImGui::Selectable( NoiseTypeToString( NoiseType::ValueCubic ).c_str(), false)) p_NoiseType = NoiseType::ValueCubic;
		if(ImGui::Selectable( NoiseTypeToString( NoiseType::Cellular ).c_str(), false)) p_NoiseType = NoiseType::Cellular;
		ImGui::EndCombo();
		m_HasNoiseChanged = true;
	}

	// Fractals
	/////////////
	ImGui::Dummy( Padding );
	ImGui::Text( "Fractals" );
	std::string SelectedFractalTypeLabel = FractalTypeToString(p_FractalType);
	if (ImGui::BeginCombo( "FractalType", SelectedFractalTypeLabel.c_str()  ))
	{
		if(ImGui::Selectable( FractalTypeToString(FractalType::None).c_str(), false)) p_FractalType = FractalType::None;
		if(ImGui::Selectable( FractalTypeToString(FractalType::FBm).c_str(), false)) p_FractalType = FractalType::FBm;
		if(ImGui::Selectable( FractalTypeToString(FractalType::PingPong).c_str(), false)) p_FractalType = FractalType::PingPong;
		if(ImGui::Selectable( FractalTypeToString(FractalType::Ridged).c_str(), false)) p_FractalType = FractalType::Ridged;
		ImGui::EndCombo();
		m_HasNoiseChanged = true;
	}
	if (ImGui::SliderInt("Octaves", &p_Octaves, 0, 10)) m_HasNoiseChanged = true;
	if (ImGui::SliderFloat("Lacunarity", &p_Lacunarity, 0.0f, 10.0f)) m_HasNoiseChanged = true;
	if (ImGui::SliderFloat( "Gain", &p_FractalGain, 0.001f, 1.0f)) m_HasNoiseChanged = true;	
	if (ImGui::SliderFloat( "Weighted Strength", &p_WeightedStrength, 0.0f, 3.0f)) m_HasNoiseChanged = true;	
	if (ImGui::SliderFloat( "Ping Pong Strength", &p_PingPongStrength, 0.0f, 5.0f)) m_HasNoiseChanged = true;	
	
	// Cellular
	/////////////
	ImGui::Dummy( Padding );
	ImGui::Text( "Cellular" );

	// Domain Warp
	/////////////
	ImGui::Dummy( Padding );
	ImGui::Text( "Domain Warp" );
	if(ImGui::Checkbox( "Enabled", &p_DomainWarpEnabled )) m_HasNoiseChanged = true;
	
}

void NoiseGenerator::SetNoiseType( NoiseType noiseType )
{
	m_FastNoiseLite.SetNoiseType(NoiseTypeToFNLEnum( noiseType ));
}


void NoiseGenerator::SetRotationType( RotationType value )
{
	m_FastNoiseLite.SetRotationType3D( RotationTypeToFNLEnum( value ) );
}

void NoiseGenerator::SetSeed( int value )
{
	m_FastNoiseLite.SetSeed( value );
}

void NoiseGenerator::SetFrequency( float value )
{
	m_FastNoiseLite.SetFrequency( value );
}

void NoiseGenerator::SetFractalType( FractalType fractalType )
{
	m_FastNoiseLite.SetFractalType( FractalTypeToFNLEnum( fractalType ) );
}

void NoiseGenerator::SetOctaves( unsigned int value )
{
	m_FastNoiseLite.SetFractalOctaves( value );
}

void NoiseGenerator::SetLacunarity( float value )
{
	m_FastNoiseLite.SetFractalLacunarity( value );
}

void NoiseGenerator::SetFractalGain( float value )
{
	m_FastNoiseLite.SetFractalGain( value );
}

void NoiseGenerator::SetWeightedStrength( float value )
{
	m_FastNoiseLite.SetFractalWeightedStrength( value );
}

void NoiseGenerator::SetPingPongEffectStrength( float value )
{
	m_FastNoiseLite.SetFractalPingPongStrength( value );
}


void NoiseGenerator::SetDomainWarpType( DomainWarpType value )
{
	m_FastNoiseLite.SetDomainWarpType( DomainWarpTypeToFNLEnum( value ) );
}

void NoiseGenerator::SetDomainWarpAmplitude( float value )
{
	m_FastNoiseLite.SetDomainWarpAmp( value );
}


FastNoiseLite::NoiseType NoiseGenerator::NoiseTypeToFNLEnum( NoiseType noiseType )
{
	switch (noiseType)
	{
		case NoiseType::OpenSimplex2: return FastNoiseLite::NoiseType_OpenSimplex2;
		case NoiseType::OpenSimplex2S: return FastNoiseLite::NoiseType_OpenSimplex2S;
		case NoiseType::Perlin: return FastNoiseLite::NoiseType_Perlin;
		case NoiseType::Value: return FastNoiseLite::NoiseType_Value;
		case NoiseType::ValueCubic: return FastNoiseLite::NoiseType_ValueCubic;
		case NoiseType::Cellular: return FastNoiseLite::NoiseType_Cellular;
	}
}
std::string NoiseGenerator::NoiseTypeToString( NoiseType noiseType ) 
{
	switch (noiseType)
	{
		case NoiseType::OpenSimplex2: return "OpenSimplex2";
		case NoiseType::OpenSimplex2S: return "OpenSimplex2S";
		case NoiseType::Perlin: return "Perlin";
		case NoiseType::Value: return "Value";
		case NoiseType::ValueCubic: return "ValueCubic";
		case NoiseType::Cellular: return "Cellular";
	}
}


FastNoiseLite::FractalType NoiseGenerator::FractalTypeToFNLEnum( FractalType fractalType )
{
	switch (fractalType)
	{
		case FractalType::None: return FastNoiseLite::FractalType_None;
		case FractalType::FBm: return FastNoiseLite::FractalType_FBm;
		case FractalType::Ridged: return FastNoiseLite::FractalType_Ridged;
		case FractalType::PingPong: return FastNoiseLite::FractalType_PingPong;
	}
}
std::string NoiseGenerator::FractalTypeToString( FractalType fractalType )
{
	switch (fractalType)
	{
		case FractalType::None: return "None";
		case FractalType::FBm: return "FBm";
		case FractalType::Ridged: return "Ridged";
		case FractalType::PingPong: return "PingPong";
	}
}

FastNoiseLite::FractalType NoiseGenerator::DomainWarpFractalTypeToFNLEnum( DomainWarpFractalType fractalType )
{
	switch (fractalType)
	{
		case DomainWarpFractalType::None: return FastNoiseLite::FractalType_None;
		case DomainWarpFractalType::FBm: return FastNoiseLite::FractalType_FBm;
		case DomainWarpFractalType::Ridged: return FastNoiseLite::FractalType_Ridged;
		case DomainWarpFractalType::PingPong: return FastNoiseLite::FractalType_PingPong;
		case DomainWarpFractalType::DomainWarpProgressive: return FastNoiseLite::FractalType_DomainWarpProgressive;
		case DomainWarpFractalType::DomainWarpIndependent: return FastNoiseLite::FractalType_DomainWarpIndependent;
	}
}
std::string NoiseGenerator::DomainWarpFractalTypeToString( DomainWarpFractalType fractalType )
{
	switch (fractalType)
	{
		case DomainWarpFractalType::None: return "None";
		case DomainWarpFractalType::FBm: return "FBm";
		case DomainWarpFractalType::Ridged: return "Ridged";
		case DomainWarpFractalType::PingPong: return "PingPong";
		case DomainWarpFractalType::DomainWarpProgressive: return "DomainWarpProgressive";
		case DomainWarpFractalType::DomainWarpIndependent: return "DomainWarpIndependent";
	}
}
FastNoiseLite::DomainWarpType NoiseGenerator::DomainWarpTypeToFNLEnum( DomainWarpType domainWarpType )
{
	switch (domainWarpType)
	{
		case DomainWarpType::BasicGrid: return FastNoiseLite::DomainWarpType_BasicGrid;
		case DomainWarpType::OpenSimplex2: return FastNoiseLite::DomainWarpType_OpenSimplex2;
		case DomainWarpType::OpenSimplex2Reduced: return FastNoiseLite::DomainWarpType_OpenSimplex2Reduced;
	}
}

FastNoiseLite::RotationType3D NoiseGenerator::RotationTypeToFNLEnum( RotationType rotationType )
{
	switch (rotationType)
	{
		case RotationType::None: return FastNoiseLite::RotationType3D_None;
		case RotationType::ImproveXYPlanes: return FastNoiseLite::RotationType3D_ImproveXYPlanes;
		case RotationType::ImproveXZPlanes: return FastNoiseLite::RotationType3D_ImproveXZPlanes;
	}
}
std::string NoiseGenerator::RotationTypeToString( RotationType rotationType )
{
	switch (rotationType)
	{
		case RotationType::None: return "None";
		case RotationType::ImproveXYPlanes: return "ImproveXYPlanes";
		case RotationType::ImproveXZPlanes: return "ImproveXZPlanes";
	}
}