#pragma once

#include "Core.h"
#include "Vuse/Events/Event.h"
#include "Vuse/Core/Timestep.h"

namespace Vuse
{
	class Layer
	{
	public:
		Layer( const char* name = "Layer" );
		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	private:
		std::string m_DebugName;
	};
}