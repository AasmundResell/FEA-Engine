#pragma once

#include "FEA_Engine/Core.h"
#include "FEA_Engine/Events/Event.h" 
#include "FEA_Engine/Events/ApplicationEvent.h"
#include "FEA_Engine/Window.h"

#include "FEA_Engine/Core/Timestep.h"

#include "FEA_Engine/LayerStack.h"

#include "FEA_Engine/ImGui/ImGuiLayer.h"


namespace FEE {

	class Application
	{
	public:
		Application(const std::string& name = "FEA App");
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

		//want to have ImGui automatically part of the application an not something the game controls
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;


	private:
		static Application* s_Instance;
	};
	
	//this needs to be defined in the application (i.e sandbox)
	Application* CreateApplication();
}
