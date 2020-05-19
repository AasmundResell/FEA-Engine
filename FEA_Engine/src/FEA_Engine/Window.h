#pragma once

#include "feepch.h"

#include "FEA_Engine\Core.h"
#include "FEA_Engine\Events\Event.h"

namespace FEE {

	//struct for the window properties
	struct WindowProps 
	{
		std::string Title;
		unsigned int Width, Height;

		WindowProps(const std::string& title = "FEA Engine",
			unsigned int width = 1280, unsigned int height = 720) :
			Title(title), Width(width), Height(height) {}
	};


	//platform independant abstract window class
	class FEE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {};

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
	
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		//this function needs to be implemented pr platform
		static Window* Create(const WindowProps& props = WindowProps());
	};


}
