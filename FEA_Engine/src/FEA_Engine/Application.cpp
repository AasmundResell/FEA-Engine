#include "feepch.h"

#include "FEA_Engine/Application.h"
#include "FEA_Engine/Log.h"
#include "Input.h"


#include "glad/glad.h"

namespace FEE {

#define  BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	//this constructor will be called when the inherited  application class is created?? ie Sandbox()
	Application::Application()
	{
		FEE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());

		//this is where the event dispatcher is called???
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
	}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		//tells the dispatcher to close the window if it discover a WindowCloseEvent
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		
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
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			//iterate and update layers in the stack
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			

			//update the window class
			m_Window->OnUpdate();
		}
	}
	
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
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
