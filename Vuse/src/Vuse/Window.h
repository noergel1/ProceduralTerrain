#pragma once

#include "vuse_pch.h"

#include "Vuse/Core.h"
#include "Vuse/Events/Event.h"
#include "Vuse/Renderer/RenderContext.h"

namespace Vuse
{

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Vuse Engine",
					unsigned int width = 1280,
					unsigned int height = 720)
			: Title(title)
			, Width(width)
			, Height(height)
		{ }
	};

	// Interface representing a desktop system based window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void( Event& )>;

		Window( const WindowProps& props = WindowProps() );
		virtual ~Window();

		void OnUpdate();

		inline void* GetWindowPtr() const { return (void*)m_Window; };
		inline unsigned int GetWidth() const { return m_Data.Width; }
		inline unsigned int GetHeight() const { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback( const EventCallbackFn& callback ) { m_Data.EventCallback = callback;  }
		void SetVSync( bool enabled );
		bool IsVSync() const;

		void CaptureMouse( bool enable );

	private:
		virtual void Init( const WindowProps& props );
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		RenderContext* m_Context;

		struct WindowData
		{
			std::string Title = "";
			unsigned int Width = 0, Height = 0;
			bool VSync = true;

			EventCallbackFn EventCallback = nullptr;
		};

		WindowData m_Data;

	};

}