#pragma once

#include "FastNoiseLite.h"

#include "Vuse.h"

enum class NoiseType
{
	OpenSimplex2,
	OpenSimplex2S,
	Cellular,
	Perlin,
	ValueCubic,
	Value
};

enum class FractalType
{
	None,
	FBm,
	Ridged,
	PingPong
};

enum class DomainWarpFractalType
{
	None,
	FBm,
	Ridged,
	PingPong,
	DomainWarpProgressive,
	DomainWarpIndependent
};

enum class DomainWarpType
{
	BasicGrid,
	OpenSimplex2,
	OpenSimplex2Reduced
};

enum class RotationType
{
	None,
	ImproveXYPlanes,
	ImproveXZPlanes,
};

class NoiseGenerator
{
public:
	NoiseGenerator();

	void UpdateNoise();

	// General
	////////////
	NoiseType p_NoiseType;
	RotationType p_RotationType;
	unsigned int p_Seed;
	float p_Frequency;

	// Fractal
	////////////
	FractalType p_FractalType;
	unsigned int p_Octaves;
	float p_Lacunarity;
	float p_Gain;
	float p_WeightedStrength;
	float p_PingPongStrength;

	// Domain Warp
	////////////
	bool p_DomainWarpEnabled;
	DomainWarpType p_DomainWarpType;
	float p_DomainWarpAmplitude;


	float GetPixel(float x, float y);
	float GetPixel(float x, float y, float z);

	
private:
	static FastNoiseLite::NoiseType NoiseTypeToFNLEnum( NoiseType noiseType );
	static FastNoiseLite::FractalType FractalTypeToFNLEnum( FractalType fractalType );
	static FastNoiseLite::FractalType DomainWarpFractalTypeToFNLEnum( DomainWarpFractalType fractalType );
	static FastNoiseLite::DomainWarpType DomainWarpTypeToFNLEnum( DomainWarpType domainWarpType );
	static FastNoiseLite::RotationType3D RotationTypeToFNLEnum( RotationType rotationType );

	void SetNoiseType( NoiseType noiseType );
	void SetRotationType( RotationType value );
	void SetSeed( unsigned int value );
	void SetFrequency( float value );
	void SetFractalType( FractalType fractalType );
	void SetOctaves( unsigned int value );
	void SetLacunarity( float value );
	void SetGain( float value );
	void SetWeightedStrength( float value );
	void SetPingPongEffectStrength( float value );

	void SetDomainWarpType( DomainWarpType value );
	void SetDomainWarpAmplitude( float value );


private:
	FastNoiseLite m_FastNoiseLite;



};