#include "NoiseGenerator.h"

#include <imgui/imgui.h>

NoiseGenerator::NoiseGenerator()
{
	SetNoiseType( NoiseType::OpenSimplex2 );
	SetRotationType( RotationType::None );
	SetSeed( 1550 );
	SetFrequency( 0.01 );
	SetFractalType( FractalType::FBm );
	SetOctaves( 5 );
	SetLacunarity( 2.0f );
	SetGain( 0.5f );
	SetWeightedStrength( 0.0f );
	SetPingPongEffectStrength( 2.0f );
	EnableDomainWarp( false );
	SetDomainWarpType( DomainWarpType::OpenSimplex2 );
	SetDomainWarpAmplitude( 30.0f );
}

bool NoiseGenerator::OnImGuiRender()
{
	bool hasChanged = false;
	if(ImGui::SliderFloat( "Frequency", &m_Frequency, 0.001, 0.15 )) hasChanged = true;
	return hasChanged;
}

void NoiseGenerator::UpdateNoise()
{
	m_FastNoiseLite.SetFrequency( m_Frequency );			
}

float NoiseGenerator::GetPixel( float x, float y )
{
	return m_FastNoiseLite.GetNoise( x, y );
}

float NoiseGenerator::GetPixel( float x, float y, float z )
{
	return m_FastNoiseLite.GetNoise( x, y, z );
}

NoiseType NoiseGenerator::GetNoiseType()
{
	return m_NoiseType;
}
void NoiseGenerator::SetNoiseType( NoiseType noiseType )
{
	m_FastNoiseLite.SetNoiseType(NoiseTypeToFNLEnum( noiseType ));
	m_NoiseType = noiseType;
}

RotationType NoiseGenerator::GetRotationType()
{
	return m_RotationType;
}
void NoiseGenerator::SetRotationType( RotationType value )
{
	m_FastNoiseLite.SetRotationType3D( RotationTypeToFNLEnum( value ) );
	m_RotationType = value;
}

unsigned int NoiseGenerator::GetSeed()
{
	return m_Seed;
}
void NoiseGenerator::SetSeed( unsigned int value )
{
	m_FastNoiseLite.SetSeed( value );
	m_Seed = value;
}

float NoiseGenerator::GetFrequency()
{
	return m_Frequency;
}
void NoiseGenerator::SetFrequency( float value )
{
	m_FastNoiseLite.SetFrequency( value );
	m_Frequency = value;
}

FractalType NoiseGenerator::GetFractalType()
{
	return m_FractalType;
}
void NoiseGenerator::SetFractalType( FractalType fractalType )
{
	m_FastNoiseLite.SetFractalType( FractalTypeToFNLEnum( fractalType ) );
	m_FractalType = fractalType;
}

unsigned int NoiseGenerator::GetOctaves()
{
	return m_Octaves;
}
void NoiseGenerator::SetOctaves( unsigned int value )
{
	m_FastNoiseLite.SetFractalOctaves( value );
	m_Octaves = value;
}

float NoiseGenerator::GetLacunarity()
{
	return m_Lacunarity;
}
void NoiseGenerator::SetLacunarity( float value )
{
	m_FastNoiseLite.SetFractalLacunarity( value );
	m_Lacunarity = value;
}

float NoiseGenerator::GetGain()
{
	return m_Gain;
}
void NoiseGenerator::SetGain( float value )
{
	m_FastNoiseLite.SetFractalGain( value );
	m_Gain = value;
}

float NoiseGenerator::GetWeightedStrength()
{
	return m_WeightedStrength;
}
void NoiseGenerator::SetWeightedStrength( float value )
{
	m_FastNoiseLite.SetFractalWeightedStrength( value );
	m_WeightedStrength = value;
}

float NoiseGenerator::GetPingPongEffectStrength()
{
	return m_PingPongStrength;
}
void NoiseGenerator::SetPingPongEffectStrength( float value )
{
	m_FastNoiseLite.SetFractalPingPongStrength( value );
	m_PingPongStrength = value;
}

bool NoiseGenerator::IsDomainWarpEnabled()
{
	return m_DomainWarpEnabled;
}
void NoiseGenerator::EnableDomainWarp( bool value )
{
	m_DomainWarpEnabled = value;
}

DomainWarpType NoiseGenerator::GetDomainWarpType()
{
	return m_DomainWarpType;
}
void NoiseGenerator::SetDomainWarpType( DomainWarpType value )
{
	m_FastNoiseLite.SetDomainWarpType( DomainWarpTypeToFNLEnum( value ) );
	m_DomainWarpType = value;
}

float NoiseGenerator::GetDomainWarpAmplitude()
{
	return m_DomainWarpAmplitude;
}
void NoiseGenerator::SetDomainWarpAmplitude( float value )
{
	m_FastNoiseLite.SetDomainWarpAmp( value );
	m_DomainWarpAmplitude = value;
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