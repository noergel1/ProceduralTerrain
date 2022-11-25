#include "vuse_pch.h"
#include "Window.h"

#include "Vuse/Log.h"
#include "Vuse/Events/ApplicationEvent.h"
#include "Vuse/Events/KeyEvent.h"
#include "Vuse/Events/MouseEvent.h"

#include <GLFW/glfw3.h>

namespace Vuse
{

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error_code, const char* description)
	{
		VUSE_CORE_ERROR( "GLFW Error ({0}): {1}", error_code, description );
	}

	Window::Window( const WindowProps& props )
	{
		Init( props );
	}

	Window::~Window()
	{
		Shutdown();
	}

	void Window::Init( const WindowProps& props )
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		VUSE_CORE_INFO( "Creating Window {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height );


		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			VUSE_CORE_ASSERT( success, "Could not initialize GLFW!" );
			glfwSetErrorCallback( GLFWErrorCallback );
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow( m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		m_Context = new RenderContext(m_Window);
		m_Context->Init();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		glfwSetWindowUserPointer( m_Window, &m_Data );
		SetVSync( true );
		CaptureMouse( false );

		// Set GLFW callbacks
		glfwSetWindowSizeCallback( m_Window, []( GLFWwindow* window, int width, int height ) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer( window );
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event( width, height );
			data.EventCallback( event );
		} );

		glfwSetWindowCloseCallback( m_Window, []( GLFWwindow* window ) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer( window );

			WindowCloseEvent event;
			data.EventCallback( event );
		} );

		glfwSetKeyCallback( m_Window, []( GLFWwindow* window, int key, int scancode, int action, int mods ) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer( window );

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event( key, 0 );
					data.EventCallback( event );
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event( key, 1 );
					data.EventCallback( event );
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event( key );
					data.EventCallback( event );
					break;
				}
			}
		} );

		glfwSetMouseButtonCallback( m_Window, []( GLFWwindow* window, int button, int action, int mods ) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event( button );
					data.EventCallback( event );
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event( button );
					data.EventCallback( event );
					break;
				}
			}
		} );

		glfwSetScrollCallback( m_Window, []( GLFWwindow* window, double xoffset, double yoffset ) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer( window );

			MouseScrolledEvent event( (float)xoffset, (float)yoffset );
			data.EventCallback( event );
		} );

		glfwSetCursorPosCallback( m_Window, []( GLFWwindow* window, double xpos, double ypos ) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer( window );

			MouseMovedEvent event( (float)xpos, (float)ypos );
			data.EventCallback( event );
		} );

	}

	void Window::Shutdown()
	{
		glfwDestroyWindow( m_Window );
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void Window::SetVSync( bool enabled )
	{
		if (enabled)
			glfwSwapInterval( 1 );
		else
			glfwSwapInterval( 0 );

		m_Data.VSync = enabled;
	}

	bool Window::IsVSync() const
	{
		return m_Data.VSync;
	}

	void Window::CaptureMouse( bool enable )
	{
		if(enable) glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

}