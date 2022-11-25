#pragma once

#include "Core.h"
#include "Window.h"

#include "Vuse/LayerStack.h"
#include "Vuse/ImGui/ImGuiLayer.h"
#include "Vuse/Events/ApplicationEvent.h"
#include "Vuse/Core/Timestep.h"

namespace Vuse {

	class Application {
	public: 
		virtual ~Application();
		Application( const Application& ) = delete;
		Application& operator=(Application& other) = delete;

		void Run();

		void OnEvent( Event& e );

		void PushLayer( Layer* layer );
		void PushOverlay ( Layer* overlay );

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	protected:
		Application();


	private:
		bool OnWindowClose( WindowCloseEvent& e );

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}

