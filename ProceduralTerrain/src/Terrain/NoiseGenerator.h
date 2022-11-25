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

	bool OnImGuiRender();

	void UpdateNoise();

	float GetPixel(float x, float y);
	float GetPixel(float x, float y, float z);

	NoiseType GetNoiseType();
	void SetNoiseType( NoiseType noiseType );

	RotationType GetRotationType();
	void SetRotationType( RotationType value );

	unsigned int GetSeed();
	void SetSeed( unsigned int value );

	float GetFrequency();
	void SetFrequency( float value );

	FractalType GetFractalType();
	void SetFractalType( FractalType fractalType );

	unsigned int GetOctaves();
	void SetOctaves( unsigned int value );

	float GetLacunarity();
	void SetLacunarity( float value );

	float GetGain();
	void SetGain( float value );

	float GetWeightedStrength();
	void SetWeightedStrength( float value );

	float GetPingPongEffectStrength();
	void SetPingPongEffectStrength( float value );

	bool IsDomainWarpEnabled();
	void EnableDomainWarp(bool value);

	DomainWarpType GetDomainWarpType();
	void SetDomainWarpType( DomainWarpType value );

	float GetDomainWarpAmplitude();
	void SetDomainWarpAmplitude( float value );

private:
	static FastNoiseLite::NoiseType NoiseTypeToFNLEnum( NoiseType noiseType );
	static FastNoiseLite::FractalType FractalTypeToFNLEnum( FractalType fractalType );
	static FastNoiseLite::FractalType DomainWarpFractalTypeToFNLEnum( DomainWarpFractalType fractalType );
	static FastNoiseLite::DomainWarpType DomainWarpTypeToFNLEnum( DomainWarpType domainWarpType );
	static FastNoiseLite::RotationType3D RotationTypeToFNLEnum( RotationType rotationType );

private:
	FastNoiseLite m_FastNoiseLite;

	NoiseType m_NoiseType = NoiseType::OpenSimplex2;
	RotationType m_RotationType;
	unsigned int m_Seed = 1337;
	float m_Frequency = 0.01f;

	// Fractal
	////////////
	FractalType m_FractalType;
	unsigned int m_Octaves;
	float m_Lacunarity;
	float m_Gain;
	float m_WeightedStrength;
	float m_PingPongStrength;

	// Domain Warp
	////////////
	bool m_DomainWarpEnabled;
	DomainWarpType m_DomainWarpType;
	float m_DomainWarpAmplitude;



};