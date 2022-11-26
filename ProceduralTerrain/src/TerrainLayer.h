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
	{
	}

	void OnUpdate(Timestep timestep) override
	{
		m_Terrain.OnUpdate();
	}

	void OnEvent( Event& event) override
	{
		
	}

	void OnImGuiRender() override
	{
		m_Terrain.OnImGuiRender();
	}

private:
	Terrain m_Terrain;
};