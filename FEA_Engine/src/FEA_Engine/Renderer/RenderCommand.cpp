#include "feepch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace FEE {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}