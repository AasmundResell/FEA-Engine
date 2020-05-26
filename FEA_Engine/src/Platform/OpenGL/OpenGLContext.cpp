#include "feepch.h"
#include "OpenGLContext.h"

#include <GLFW\glfw3.h>
#include <glad/glad.h>


namespace FEE {



	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		FEE_CORE_ASSERT(windowHandle, "Window handle is null")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FEE_CORE_ASSERT(status, "Failed to initialize Glad!");

		FEE_CORE_INFO("OpenGL Info: ");
		FEE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		FEE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		FEE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);

	}

}