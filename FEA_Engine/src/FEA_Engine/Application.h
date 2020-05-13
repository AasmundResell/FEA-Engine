#pragma once

#include "Core.h"

namespace FEE {

	class FEE_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void run();
	};
	
	//this is to be defined in an application
	Application* CreateApplication();
}
