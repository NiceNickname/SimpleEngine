#include <Engine.h>

#define MAX_TEXTURES 32

class OpenGLGame : public Engine::App
{
public:
	std::shared_ptr<Engine::VertexArray> m_VAO;
	std::shared_ptr<Engine::Shader> m_Shader;
	std::shared_ptr<Engine::Shader> m_BatchShader;
	std::shared_ptr<Engine::Texture> m_Texture;
	std::shared_ptr<Engine::Camera> m_Camera;

	

	void ChooseApi() override
	{
		m_Api = Engine::Renderer2D::API::OPENGL;
	}

	virtual void Start() override
	{
		Engine::Renderer2D::SetVSync(true);
		Engine::Renderer2D::SetClearColor({0.0f, 0.0f, 1.0f, 1.0f});

		float vertices[] = {
			-10.0f, -10.0f, 0.0f, 0.0f, 0.0f,
			-10.0f,  -5.0f, 0.0f, 0.0f, 1.0f,
			 -5.0f,  -5.0f, 0.0f, 1.0f, 1.0f,
			 -5.0f, -10.0f, 0.0f, 1.0f, 0.0f
		};

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0
		};

		std::shared_ptr<Engine::VertexBuffer> vertexbuffer;
		vertexbuffer.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));
		
		std::shared_ptr<Engine::IndexBuffer> indexbuffer;
		indexbuffer.reset(Engine::IndexBuffer::Create(indices, sizeof(indices)));

		m_Camera = std::make_shared<Engine::Camera>(glm::perspectiveFov(glm::radians(45.0f), 1280.0f, 720.0f, 0.1f, 10000.0f));
		

		Engine::VertexBufferLayout layout = { {"positions", Engine::DATATYPE::FLOAT3 },
											  {"texCoord", Engine::DATATYPE::FLOAT2} };

		vertexbuffer->SetLayout(layout);

		m_VAO = std::make_shared<Engine::VertexArray>();
		m_VAO->SetVB(vertexbuffer);
		m_VAO->SetIB(indexbuffer);

		m_Shader.reset(Engine::Shader::Create("res/shaders/shader.vert", "res/shaders/shader.fragm"));
		
		m_Shader->Bind();
		m_Shader->SetUniform1i("tex", 1);
		m_Shader->SetUniformMat4f("view", m_Camera->GetProjectionMatrix() * m_Camera->GetViewMatrix());

		m_Texture.reset(Engine::Texture::Create("res/textures/checkerboard.jpg"));
		

		m_BatchShader = std::make_shared<Engine::OpenGLShader>("res/shaders/BatchShader.vert", "res/shaders/BatchShader.fragm");
		m_BatchShader->Bind();
		m_BatchShader->SetUniformMat4f("view", m_Camera->GetProjectionMatrix() * m_Camera->GetViewMatrix());

		
		int samplers[MAX_TEXTURES];
		for (int i = 0; i < MAX_TEXTURES; i++)
			samplers[i] = i;

		m_BatchShader->SetUniformIntArray("u_Textures", sizeof(samplers), samplers);

	}

	void Update() override
	{
		m_Camera->Update();

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("view", m_Camera->GetProjectionMatrix() * m_Camera->GetViewMatrix());

		m_BatchShader->Bind();
		m_BatchShader->SetUniformMat4f("view", m_Camera->GetProjectionMatrix() *  m_Camera->GetViewMatrix());
		
	}

	void Render() override
	{
		m_BatchShader->Bind();

		Engine::Renderer2D::Begin();

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				glm::vec4 color = { 1.0f, 0.0f, 0.0f, 1.0f };
				Engine::Renderer2D::DrawQuad({ j, i, 0.0f }, { 0.8f, 0.8f }, color);
				Engine::Renderer2D::DrawQuad({ j + 5, i, 0.0f }, { 0.8f, 0.8f}, m_Texture);
			}
		}

		Engine::Renderer2D::End();
		
		Engine::Renderer2D::Draw();

		m_Shader->Bind();
		m_VAO->Bind();
		m_VAO->Draw();
	}

	void ImGuiRender() override
	{
		ImGui::Begin("Render stats");
		ImGui::Text("Draw Calls: %d", Engine::Renderer2D::GetStats().DrawCallsCount);
		ImGui::Text("Quads Count: %d", Engine::Renderer2D::GetStats().QuadsCount);
		ImGui::Text("Quads Per Draw Call: %d", Engine::Renderer2D::GetStats().QuadPerDrawCall);
		ImGui::End();

		ImGui::Begin("Camera stats");
		ImGui::Text("Camera position: %f, %f, %f", m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z);
		ImGui::Text("Camera focal point: %f, %f, %f", m_Camera->GetFocalPoint().x, m_Camera->GetFocalPoint().y, m_Camera->GetFocalPoint().z);
		ImGui::Text("Distance from camera to focal point: %f", m_Camera->GetDistance());
		ImGui::End();
	}


	void OnMouseScrolled(Engine::MouseScrolledEvent& e) override
	{
		m_Camera->MouseZoom(e.m_YOffset);
	}
};


#if OpenGL
#include "EntryPoint.h"
Engine::App* CreateApp()
{
	return new OpenGLGame();
}
#endif