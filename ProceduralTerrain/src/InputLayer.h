#pragma once

#include "Vuse.h"

#include "imgui/imgui.h"

class InputLayer : public Vuse::Layer
{
public:
	InputLayer( Vuse::Camera& camera )
		:Layer("Input")
		,m_Camera(camera)
	{}

	void OnUpdate(Vuse::Timestep timestep) override
	{
		float deltaTime = timestep;

		if (Vuse::Input::IsKeyPressed( VUSE_KEY_W ))
		{
			glm::vec3 camPos = m_Camera.GetPosition();
			glm::vec3 camFront = m_Camera.GetViewDirection();
			m_Camera.SetPosition( camPos + (camFront * m_MoveSpeed) * deltaTime );
		}

		if (Vuse::Input::IsKeyPressed( VUSE_KEY_A ))
		{
			glm::vec3 camPos = m_Camera.GetPosition();
			glm::vec3 camRight = m_Camera.GetRightVector();
			m_Camera.SetPosition( camPos - (camRight * m_MoveSpeed) * deltaTime );
		}

		if (Vuse::Input::IsKeyPressed( VUSE_KEY_S ))
		{
			glm::vec3 camPos = m_Camera.GetPosition();
			glm::vec3 camFront = m_Camera.GetViewDirection();
			m_Camera.SetPosition( camPos - (camFront * m_MoveSpeed) * deltaTime );
		}

		if (Vuse::Input::IsKeyPressed( VUSE_KEY_D ))
		{
			glm::vec3 camPos = m_Camera.GetPosition();
			glm::vec3 camRight = m_Camera.GetRightVector();
			m_Camera.SetPosition( camPos + (camRight * m_MoveSpeed) * deltaTime);
		}


	}

	void OnEvent( Vuse::Event& event) override
	{
		Vuse::EventDispatcher dispatcher( event );


		dispatcher.Dispatch<Vuse::KeyPressedEvent>( [this]( Vuse::KeyPressedEvent& e ) {
			if (e.GetKeyCode() == VUSE_KEY_TAB && e.GetRepeatCount() == 0)
			{
				m_IsMouseCaptured = !m_IsMouseCaptured;
				m_MouseAlreadyMoved = false;
				Vuse::Application::Get().GetWindow().CaptureMouse( m_IsMouseCaptured );

				return true;
			}
		} );

		ImGuiIO& io = ImGui::GetIO();
		Vuse:: EventType eventType = event.GetEventType();
		if (!m_IsMouseCaptured && eventType == Vuse::EventType::KeyPressed || eventType == Vuse::EventType::KeyReleased)
		{
			dispatcher.Dispatch<Vuse::KeyPressedEvent>( [this]( Vuse::KeyPressedEvent& e ) {
				return true;
				} );
			dispatcher.Dispatch<Vuse::KeyReleasedEvent>( [this]( Vuse::KeyReleasedEvent& e ) {
				return true;
				} );
			return;
		};
		if (!m_IsMouseCaptured && eventType == Vuse::EventType::MouseMoved || eventType == Vuse::EventType::MouseScrolled 
								|| eventType == Vuse::EventType::MouseButtonPressed || eventType == Vuse::EventType::MouseButtonReleased)
		{
			dispatcher.Dispatch<Vuse::MouseMovedEvent>( [this]( Vuse::MouseMovedEvent& e ) {
				return true;
				} );
			dispatcher.Dispatch<Vuse::MouseButtonPressedEvent>( [this]( Vuse::MouseButtonPressedEvent& e ) {
				return true;
				} );			
			dispatcher.Dispatch<Vuse::MouseButtonReleasedEvent>( [this]( Vuse::MouseButtonReleasedEvent& e ) {
				return true;
				} );
			return;
		};



		dispatcher.Dispatch<Vuse::MouseMovedEvent>( [this]( Vuse::MouseMovedEvent& e ) {

			if (!m_MouseAlreadyMoved)
			{
				m_MouseAlreadyMoved = true;
				m_LastMouseX = e.GetX();
				m_LastMouseY = e.GetY();
				return true;
			}

			float mouseX = e.GetX();
			float mouseY = e.GetY();

			float xOffset = mouseX - m_LastMouseX;
			float yOffset = mouseY - m_LastMouseY;

			float newYaw = m_Camera.GetYaw() + (xOffset * m_TurnSpeed);
			float newPitch = m_Camera.GetPitch() - (yOffset * m_TurnSpeed);
			if (newPitch >= 90.0f) newPitch = 89.9f;
			if (newPitch <= -90.0f) newPitch = -89.9f;

			m_Camera.SetYaw( newYaw );
			m_Camera.SetPitch( newPitch );

			m_LastMouseX = mouseX;
			m_LastMouseY = mouseY;

			return true;
			} );



	}

private:

private:
	Vuse::Camera& m_Camera;


	// mouse values
	float m_LastMouseX = 0.0f;
	float m_LastMouseY = 0.0f;
	float m_MouseAlreadyMoved = false;
	bool m_IsMouseCaptured = true;

	// movement values
	float m_MoveSpeed = 2.5f;
	float m_TurnSpeed = 0.1f;
};