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

enum class CellularDistanceFunction {
	Euclidean,
	EuclideanSq,
	Hybrid,
	Manhattan
};

enum class CellularReturnType {
	CellValue,
	Distance,
	Distance2,
	Distance2Add,
	Distance2Div,
	Distance2Mul,
	Distance2Sub,
};

class NoiseGenerator
{
public:
	NoiseGenerator();

	void UpdateNoiseSettings();
	void UpdateNoisePreview();

	void OnUpdate();
	void OnImGuiRender();

	float GetPixel(float x, float y);
	float GetPixel(float x, float y, float z);

public:
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

	// Cellular
	////////////
	CellularDistanceFunction p_CellularDistanceFunc;
	CellularReturnType p_CellularReturnType;
	float p_CellularJitter;

	// Domain Warp
	////////////
	bool p_DomainWarpEnabled;
	DomainWarpType p_DomainWarpType;
	float p_DomainWarpAmplitude;
	
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
	static FastNoiseLite::CellularDistanceFunction CellularDistanceFuncToFNLEnum( CellularDistanceFunction distanceFunction );
	static std::string CellularDistanceFuncToString( CellularDistanceFunction distanceFunction );
	static FastNoiseLite::CellularReturnType CellularReturnTypeToFNLEnum( CellularReturnType returnType );
	static std::string CellularReturnTypeToString( CellularReturnType returnType  );

private:
	FastNoiseLite m_FastNoiseLite;

	// noise preview image
	bool m_HasNoiseChanged;
	Texture_2D* m_NoisePreview;
	unsigned char* m_NoisePreviewData;
	const unsigned int m_NoisePreviewWidth;
	const unsigned int m_NoisePreviewHeight;
};