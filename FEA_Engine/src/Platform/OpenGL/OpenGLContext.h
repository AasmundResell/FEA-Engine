#pragma once

#include "FEA_Engine/Renderer/GraphicsContext.h"

//forward declaration
struct GLFWwindow;

namespace FEE {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:

		GLFWwindow* m_WindowHandle;

	};

}