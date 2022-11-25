#include "vuse_pch.h"
#include "Input.h"

#include "Vuse/Application.h"

#include <GLFW/glfw3.h>

namespace Vuse
{
	bool Input::IsKeyPressedImpl( int keycode ) const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowPtr());
		auto state = glfwGetKey( window, keycode );
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	};

	bool Input::IsMouseButtonPressedImpl( int button ) const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowPtr());
		auto state = glfwGetMouseButton( window, button );
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosImpl() const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowPtr());
		double xpos, ypos;
		glfwGetCursorPos( window, &xpos, &ypos );
		return {(float)xpos, (float)ypos};
	}

	float Input::GetMouseXImpl() const
	{
		auto [x, y] = GetMousePosImpl();
		return x;
	}

	float Input::GetMouseYImpl() const
	{
		auto [x, y] = GetMousePosImpl();
		return y;
	}
}