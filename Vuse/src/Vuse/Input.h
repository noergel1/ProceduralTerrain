#pragma once

#include "Vuse/Core.h"

namespace Vuse
{
	class Input
	{
	public:
		inline static const Input& Get() { 
			static Input s_Instance;
			return s_Instance; 
		} const

		Input( const Input& ) = delete;
		Input& operator=(Input& other) = delete;

	private:
		Input() {};

	public:
		inline static bool IsKeyPressed( int keycode ) { return Get().IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return Get().IsMouseButtonPressedImpl( button ); }
		inline static std::pair<float, float> GetMousePos() { return Get().GetMousePosImpl(); }
		inline static float GetMouseX() { return Get().GetMouseXImpl(); }
		inline static float GetMouseY() { return Get().GetMouseYImpl(); }

	private:
		bool IsKeyPressedImpl( int keycode ) const;
		bool IsMouseButtonPressedImpl( int button ) const;
		std::pair<float, float> GetMousePosImpl() const;
		float GetMouseXImpl() const;
		float GetMouseYImpl() const;
	};
}