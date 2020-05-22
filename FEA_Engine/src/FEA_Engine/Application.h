#pragma once

#include "FEA_Engine/Core.h"
#include "FEA_Engine/Events/Event.h" 
#include "FEA_Engine/Events/ApplicationEvent.h"
#include "FEA_Engine/Window.h"

#include "FEA_Engine/Layer.h"
#include "FEA_Engine/LayerStack.h"

namespace FEE {

	class FEE_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline Window& GetWindow() { return *m_Window; }
		
		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e); 

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};
	
	//this needs to be defined in the application (i.e sandbox)
	Application* CreateApplication();
}
