#pragma once

#include "FastNoiseLite.h"

#include "Vuse.h"

using namespace Vuse;

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

	void UpdateNoiseSettings();
	void UpdateNoisePreview();

	void OnUpdate();
	void OnImGuiRender();

	// General
	////////////
	NoiseType p_NoiseType;
	RotationType p_RotationType;
	int p_Seed;
	float p_Frequency;

	// Fractal
	////////////
	FractalType p_FractalType;
	int p_Octaves;
	float p_Lacunarity;
	float p_FractalGain;
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
	static std::string NoiseTypeToString( NoiseType noiseType );
	static FastNoiseLite::FractalType FractalTypeToFNLEnum( FractalType fractalType );
	static std::string FractalTypeToString( FractalType fractalType );
	static FastNoiseLite::FractalType DomainWarpFractalTypeToFNLEnum( DomainWarpFractalType fractalType );
	static std::string DomainWarpFractalTypeToString( DomainWarpFractalType fractalType );
	static FastNoiseLite::DomainWarpType DomainWarpTypeToFNLEnum( DomainWarpType domainWarpType );
	static std::string DomainWarpTypeToString( DomainWarpType domainWarpType );
	static FastNoiseLite::RotationType3D RotationTypeToFNLEnum( RotationType rotationType );
	static std::string RotationTypeToString( RotationType rotationType );

	void SetNoiseType( NoiseType noiseType );
	void SetRotationType( RotationType value );
	void SetSeed( int value );
	void SetFrequency( float value );
	void SetFractalType( FractalType fractalType );
	void SetOctaves( unsigned int value );
	void SetLacunarity( float value );
	void SetFractalGain( float value );
	void SetWeightedStrength( float value );
	void SetPingPongEffectStrength( float value );

	void SetDomainWarpType( DomainWarpType value );
	void SetDomainWarpAmplitude( float value );


private:
	FastNoiseLite m_FastNoiseLite;

	// noise preview image
	bool m_HasNoiseChanged = true;
	Texture_2D* m_NoisePreview;
	unsigned char* m_NoisePreviewData;
	const unsigned int m_NoisePreviewWidth = 300;
	const unsigned int m_NoisePreviewHeight = 300;
};