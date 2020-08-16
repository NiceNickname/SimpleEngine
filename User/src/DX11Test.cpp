#include "Engine.h"


class DX11Game : public Engine::App
{

public:
	std::shared_ptr<Engine::Shader> m_Shader;
	std::shared_ptr<Engine::OrthographicCamera> m_Camera;
	std::shared_ptr<Engine::Texture> m_Texture;

	glm::vec3 CameraPosition = { 0.0f, 0.0f, 0.0f };
	

	void ChooseApi() override
	{
		m_Api = Engine::Renderer2D::API::DX11;
	}
	void Start() override
	{

		Engine::Renderer2D::SetVSync(true);
		Engine::Renderer2D::SetClearColor({ 0.0f, 0.2f, 0.4f, 1.0f });

		m_Texture.reset(Engine::Texture::Create("res/textures/checkerboard.jpg"));
		m_Texture->Bind(1);

		m_Camera = std::make_shared<Engine::OrthographicCamera>(16.0f / 9.0f);
		m_Camera->SetPosition(CameraPosition);


		m_Shader.reset(Engine::Shader::Create("res/shaders/VertexShader.cso", "res/shaders/PixelShader.cso"));
		m_Shader->Bind();

		Engine::UniformElement layout[] = { {"view", Engine::DATATYPE::MAT4}  };

		m_Shader->SetUniformLayout(layout, sizeof(layout) / sizeof(Engine::UniformElement));

	}

	void Update() override
	{
		if (Engine::Input::IsKeyDown(ENGINE_KEY_RIGHT))
			CameraPosition.x += m_Camera->GetSpeed();
		if (Engine::Input::IsKeyDown(ENGINE_KEY_LEFT))
			CameraPosition.x -= m_Camera->GetSpeed();
		if (Engine::Input::IsKeyDown(ENGINE_KEY_UP))
			CameraPosition.y += m_Camera->GetSpeed();
		if (Engine::Input::IsKeyDown(ENGINE_KEY_DOWN))
			CameraPosition.y -= m_Camera->GetSpeed();

		m_Camera->SetPosition(CameraPosition);
		m_Shader->SetUniformMat4f("view", m_Camera->GetProjection() * m_Camera->GetView());
	}

	void Render() override
	{
		Engine::Renderer2D::Begin();

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				glm::vec4 color = { 1.0f, 0.0f, 0.0f, 1.0f };
				Engine::Renderer2D::DrawQuad({ j, i, 0.0f }, { 0.8f, 0.8f }, color);
				Engine::Renderer2D::DrawQuad({ j + 5, i, 0.0f }, { 0.8f, 0.8f }, m_Texture);
			}
		}

		Engine::Renderer2D::End();

		Engine::Renderer2D::Draw();
	}

	void ImGuiRender() override
	{
		ImGui::Begin("Render stats");
		ImGui::Text("Draw Calls: %d", Engine::Renderer2D::GetStats().DrawCallsCount);
		ImGui::Text("Quads Count: %d", Engine::Renderer2D::GetStats().QuadsCount);
		ImGui::Text("Quads Per Draw Call: %d", Engine::Renderer2D::GetStats().QuadPerDrawCall);
		ImGui::Text("Camera position: %f, %f, %f", CameraPosition.x, CameraPosition.y, CameraPosition.z);
		ImGui::End();
	}

	void OnMouseScrolled(Engine::MouseScrolledEvent& e)
	{
		m_Camera->Zoom(e.m_YOffset);
	}

};


#if DirectX11
#include "EntryPoint.h"
Engine::App* CreateApp()
{
	return new DX11Game();
}
#endif



