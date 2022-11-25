#include "vuse_pch.h"
#include "Application.h"

#include "Vuse/Log.h"
#include "Input.h"

#include "Vuse/Renderer/Renderer.h"
#include "Vuse/Renderer/API/Debugger.h"

namespace Vuse {

#define BIND_EVENT_FN(x) std::bind( &Application::x, this, std::placeholders::_1) 

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		VUSE_CORE_ASSERT( !s_Instance, "Application already exists!" );
		s_Instance = this;

		m_Window = std::make_unique<Window>();
		m_Window->SetEventCallback( BIND_EVENT_FN( OnEvent ) );

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay( m_ImGuiLayer );
	};

	Application::~Application() {

	};

	void Application::Run() {

		glDebugger debugger;
		debugger.enableDebug();

		while (m_Running)
		{
			float time = glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		};
	}

	void Application::OnEvent( Event& e )
	{
		float time = glfwGetTime();
		Timestep timestep = time - m_LastFrameTime;

		EventDispatcher dispatcher( e );
		dispatcher.Dispatch<WindowCloseEvent>( BIND_EVENT_FN( OnWindowClose ) );

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent( e);
			if (e.IsHandled())
				break;
		}
	}

	void Application::PushLayer( Layer* layer )
	{
		m_LayerStack.PushLayer( layer );
		layer->OnAttach();
	}

	void Application::PushOverlay( Layer* overlay )
	{
		m_LayerStack.PushOverlay( overlay );
		overlay->OnAttach();
	}

	bool Application::OnWindowClose( WindowCloseEvent& e )
	{
		m_Running = false;
		return true;
	}


}
