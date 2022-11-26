#include "vuse_pch.h"
#include "RenderContext.h"

#include "Vuse/Log.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>


namespace Vuse
{
	RenderContext::RenderContext( GLFWwindow* window )
		:m_WindowHandle(window)
	{
		VUSE_CORE_ASSERT( window, "Window handle is null!" );
	}

	void RenderContext::Init()
	{
		glfwMakeContextCurrent( m_WindowHandle );
		int status = gladLoadGL( glfwGetProcAddress );
		VUSE_CORE_ASSERT( status, "Failed to initialize Glad!");
	}

	void RenderContext::SwapBuffers()
	{
		glfwSwapBuffers( m_WindowHandle );
	}
}