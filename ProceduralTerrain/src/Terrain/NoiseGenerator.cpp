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
	SetDomainWarpType( DomainWarpType::OpenSimplex2 );
	SetDomainWarpAmplitude( 30.0f );
}

void NoiseGenerator::UpdateNoise()
{
	m_FastNoiseLite.SetFrequency( p_Frequency );
	m_FastNoiseLite.SetFractalGain( p_Gain );
}

float NoiseGenerator::GetPixel( float x, float y )
{
	return m_FastNoiseLite.GetNoise( x, y );
}

float NoiseGenerator::GetPixel( float x, float y, float z )
{
	return m_FastNoiseLite.GetNoise( x, y, z );
}

void NoiseGenerator::SetNoiseType( NoiseType noiseType )
{
	m_FastNoiseLite.SetNoiseType(NoiseTypeToFNLEnum( noiseType ));
	p_NoiseType = noiseType;
}


void NoiseGenerator::SetRotationType( RotationType value )
{
	m_FastNoiseLite.SetRotationType3D( RotationTypeToFNLEnum( value ) );
	p_RotationType = value;
}

void NoiseGenerator::SetSeed( unsigned int value )
{
	m_FastNoiseLite.SetSeed( value );
	p_Seed = value;
}

void NoiseGenerator::SetFrequency( float value )
{
	m_FastNoiseLite.SetFrequency( value );
	p_Frequency = value;
}

void NoiseGenerator::SetFractalType( FractalType fractalType )
{
	m_FastNoiseLite.SetFractalType( FractalTypeToFNLEnum( fractalType ) );
	p_FractalType = fractalType;
}

void NoiseGenerator::SetOctaves( unsigned int value )
{
	m_FastNoiseLite.SetFractalOctaves( value );
	p_Octaves = value;
}

void NoiseGenerator::SetLacunarity( float value )
{
	m_FastNoiseLite.SetFractalLacunarity( value );
	p_Lacunarity = value;
}

void NoiseGenerator::SetGain( float value )
{
	m_FastNoiseLite.SetFractalGain( value );
	p_Gain = value;
}

void NoiseGenerator::SetWeightedStrength( float value )
{
	m_FastNoiseLite.SetFractalWeightedStrength( value );
	p_WeightedStrength = value;
}

void NoiseGenerator::SetPingPongEffectStrength( float value )
{
	m_FastNoiseLite.SetFractalPingPongStrength( value );
	p_PingPongStrength = value;
}


void NoiseGenerator::SetDomainWarpType( DomainWarpType value )
{
	m_FastNoiseLite.SetDomainWarpType( DomainWarpTypeToFNLEnum( value ) );
	p_DomainWarpType = value;
}

void NoiseGenerator::SetDomainWarpAmplitude( float value )
{
	m_FastNoiseLite.SetDomainWarpAmp( value );
	p_DomainWarpAmplitude = value;
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