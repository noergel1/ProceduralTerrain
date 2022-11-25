#include "Vuse.h"
#include "Vuse/EntryPoint.h"

#include "InputLayer.h"
#include "TerrainLayer.h"

#include <iostream>


class ExampleLayer : public Vuse::Layer
{
public: 
	ExampleLayer(Vuse::Camera& camera)
		:Layer( "Example" )
		,m_Camera(camera)
		,m_Shader( "src/Shader/vs.glsl", "src/Shader/fs.glsl" )
		,m_Texture(Vuse::Texture_2D( "src/Assets/Textures/floor_texture.png", Vuse::Texture_2D::TextureSettings() ))
	{ 
	}

	void OnUpdate(Vuse::Timestep timestep) override
	{
		m_Shader.Bind();
	
		m_Shader.SetMat4( "view", m_Camera.GetViewMatrix() );
		m_Shader.SetMat4( "projection", m_Camera.GetProjectionMatrix() );
		m_Shader.SetMat4( "model", glm::mat4(1.0f) );


		Vuse::RenderCommand::SetClearColor(glm::vec4( 0.2f, 0.2f, 0.2f, 1.0f ));

		float vertices[3 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.0f,  0.5f, 0.0f, 0.5f, 0.5f
		};

		Vuse::Texture::SetActiveTextureSlot( 0 );
		m_Shader.SetInt( "diffuse", 0 );
		m_Texture.Bind();

		std::shared_ptr<Vuse::VertexArray> vertexArray( new Vuse::VertexArray());

		std::shared_ptr<Vuse::VertexBuffer> vertexBuffer( new Vuse::VertexBuffer(vertices, sizeof( vertices )) );
		{
			Vuse::BufferLayout layout = {
				{Vuse::ShaderDataType::Float3, "m_Position"},
				{Vuse::ShaderDataType::Float2, "m_TexCoord"}
			};

			vertexBuffer->SetLayout( layout );
		}

		unsigned int indices[3] = {
			0, 1, 2
		};

		std::shared_ptr<Vuse::IndexBuffer> indexBuffer( new Vuse::IndexBuffer( indices, sizeof(indices)/sizeof(unsigned int) ) );

		vertexArray->AddVertexBuffer( vertexBuffer );
		vertexArray->SetIndexBuffer( indexBuffer );
		
		Vuse::RenderCommand::Clear();

		Vuse::Renderer::BeginScene();
		Vuse::Renderer::SubmitGeometry( vertexArray );
		Vuse::Renderer::EndScene();

		m_Texture.Unbind();
	}

	void OnEvent( Vuse::Event& event ) override
	{
		if (Vuse::Input::IsKeyPressed( VUSE_KEY_TAB ))
		{
			VUSE_TRACE( "TAB key is pressed!");
		}
	}

	void OnImGuiRender() override
	{

	}

private:
	Vuse::Texture_2D m_Texture;
	Vuse::Shader m_Shader;
	Vuse::Camera& m_Camera;
};

class Sandbox : public Vuse::Application {
public:
	Sandbox()
		:m_Camera(
			Vuse::ProjectionMatrix( 45.0f, 1280 / 720, 0.1f, 100.0f ),
			glm::vec3( 0.0f, 0.0f, 1.0f )
		)
	{
		Vuse::RenderCommand::EnableFaceCulling( true );
		Vuse::RenderCommand::SetCullFace( Vuse::CullFaces::BACK );
		Vuse::RenderCommand::SetFrontFace( Vuse::FrontFace::COUNTERCLOCKWISE );

		PushLayer( new ExampleLayer( m_Camera ) );
		PushLayer( new TerrainLayer( m_Camera ) );
		PushLayer( new InputLayer( m_Camera ) );
	}

	~Sandbox() {

	}

private:
	Vuse::Camera m_Camera;
};

Vuse::Application* Vuse::CreateApplication() {
	return new Sandbox();
}
