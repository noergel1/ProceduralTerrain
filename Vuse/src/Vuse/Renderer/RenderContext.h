#pragma once

class GLFWwindow;

namespace Vuse
{
	class RenderContext
	{
	public:
		RenderContext( GLFWwindow* window );

		void Init();
		void SwapBuffers();

	private:
		GLFWwindow* m_WindowHandle;
	};
}