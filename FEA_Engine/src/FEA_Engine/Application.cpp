#include "Application.h"

#include "FEA_Engine\Events\ApplicationEvent.h"
#include "FEA_Engine\Log.h"

namespace FEE {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			FEE_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			FEE_ERROR(e);
		}
		while (true);
	}
	

}
