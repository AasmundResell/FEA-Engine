#pragma once

#include "Core.h"
#include "Events\Event.h"

namespace FEE {

	class FEE_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void run();
	};
	
	//this needs to be defined in the application
	Application* CreateApplication();
}
