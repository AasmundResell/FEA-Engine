#include "feepch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace FEE {

	

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: 
			{
				FEE_CORE_ASSERT(false, "RendererAPI::None is not supported!")
				return nullptr;
			}
			case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}

		FEE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}

}