#pragma once

#include "Vuse/Layer.h"
namespace Vuse
{

	class ImGuiLayer : public Layer
	{
	public: 
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();
	};

}