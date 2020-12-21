#include "FEA_Engine.h"

#include "Platform/OpenGL/OpenGLShader.h"
  
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include "FEA_Engine/Renderer/Shader.h"

class ExampleLayer : public FEE::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquarePos(0.0f)
	{
		m_VertexArray.reset(FEE::VertexArray::Create());

		//the default GLFW space is from -1:1 in x,y,z
		float vertices[3 * 7] =
		{
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		FEE::Ref<FEE::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(FEE::VertexBuffer::Create(vertices, sizeof(vertices)));

		FEE::BufferLayout layout = {
			{  FEE::ShaderDataType::Float3,"a_Position", },
			{  FEE::ShaderDataType::Float4,"a_Color", },
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };

		FEE::Ref<FEE::IndexBuffer> indexBuffer;
		indexBuffer.reset(FEE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(FEE::VertexArray::Create());

		float squareVertices[5 * 4] =
		{
		 -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		 -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		FEE::Ref<FEE::VertexBuffer> squareVB;
		squareVB.reset(FEE::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{  FEE::ShaderDataType::Float3,"a_Position" },
			{  FEE::ShaderDataType::Float2,"a_TexCoord" }
			});
		m_SquareVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		FEE::Ref<FEE::IndexBuffer> squareIB;
		squareIB.reset(FEE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform; 
			
			out vec3 v_Position;
			out vec4 v_Color;

			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position , 1);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
		
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = vec4(v_Position + 0.5, 1.0); 
				color = v_Color;	
			}
		)";

		m_Shader = FEE::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform; 
		
			out vec3 v_Position;
			

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position , 1);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
		
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			uniform vec3 u_Color;
			
			void main()
			{
				color = vec4(u_Color,1.0);
			}
		)";

		m_FlatColorShader = FEE::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);



		m_TextureShader = FEE::Shader::Create("assets/shaders/Texture.glsl");
		m_Texture = FEE::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = FEE::Texture2D::Create("assets/textures/logo.png");

		std::dynamic_pointer_cast<FEE::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<FEE::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

	}
	

	void OnUpdate(FEE::Timestep ts ) override
	{
	
		if (FEE::Input::IsKeyPressed(FEE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (FEE::Input::IsKeyPressed(FEE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (FEE::Input::IsKeyPressed(FEE_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts; 
		else  if (FEE::Input::IsKeyPressed(FEE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (FEE::Input::IsKeyPressed(FEE_KEY_J))
			m_SquarePos.x -= m_SquareMoveSpeed * ts;
		else if (FEE::Input::IsKeyPressed(FEE_KEY_L))
			m_SquarePos.x += m_SquareMoveSpeed * ts;

		if (FEE::Input::IsKeyPressed(FEE_KEY_I))
			m_SquarePos.y += m_SquareMoveSpeed * ts;
		else  if (FEE::Input::IsKeyPressed(FEE_KEY_K))
			m_SquarePos.y -= m_SquareMoveSpeed * ts;

		if (FEE::Input::IsKeyPressed(FEE_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (FEE::Input::IsKeyPressed(FEE_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		FEE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		FEE::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		FEE::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

 
		std::dynamic_pointer_cast<FEE::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<FEE::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color",m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f,y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;		
				FEE::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, transform);
			}
		}

		m_Texture->Bind();
		FEE::Renderer::Submit(m_TextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_LogoTexture->Bind();
		FEE::Renderer::Submit(m_TextureShader, m_SquareVertexArray,
			glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		FEE::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
	
	void OnEvent(FEE::Event& event) override
	{
	}


private:

	FEE::ShaderLibrary m_ShaderLibrary;
	//drawing triangle
	FEE::Ref<FEE::Shader> m_Shader;
	FEE::Ref<FEE::VertexArray> m_VertexArray;

	//drawing square
	FEE::Ref<FEE::Shader> m_FlatColorShader, m_TextureShader;
	FEE::Ref<FEE::VertexArray> m_SquareVertexArray;

	FEE::Ref<FEE::Texture2D> m_Texture, m_LogoTexture ;

	FEE::OrthoGraphicCamera m_Camera;
	glm::vec3 m_CameraPosition;

	float m_CameraMoveSpeed = 4.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
	float m_SquareMoveSpeed = 2.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
	glm::vec3 m_SquarePos;

};

class Sandbox : public FEE::Application
{
public: 
	Sandbox() : Application("Sandbox")
	{
		PushLayer(new ExampleLayer());
		
	}

	~Sandbox()
	{

	}


};


FEE::Application* FEE::CreateApplication()
{
	//creates the specific instant of this sandbox
	return new Sandbox();
	
}