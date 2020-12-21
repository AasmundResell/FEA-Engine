#include "feepch.h"

#include "Application.h"

#include "FEA_Engine/Log.h"
#include "FEA_Engine/Renderer/Renderer.h"
#include "Input.h"

#include <glfw/glfw3.h>


namespace FEE {

#define  BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	//this constructor will be called when the inherited  application class is created?? ie Sandbox()
	Application::Application(const std::string& name)
	{
		FEE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create(WindowProps(name)));

		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Window->SetVSync(false);

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();

		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application()
	{
	}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		//tells the dispatcher to close the window if it discover a WindowCloseEvent
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		
		//backwards loop to check for events in the layers
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}


	}

	void Application::run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime(); 
			Timestep timestep = time - m_LastFrameTime; //delta time
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				//iterate and update layers in the stack
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(timestep);
				}
			} 
				//start rendering of the ImGui layer
				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
				{
					layer->OnImGuiRender();
				}
				//end Imgui
				m_ImGuiLayer->End();

			//update the window class
			m_Window->OnUpdate();
		}
	}
	
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
}
