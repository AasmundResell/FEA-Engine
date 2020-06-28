#pragma once

#include <glm/glm.hpp>
#include "RendererAPI.h"

namespace FEE {

	class RenderCommand
	{
		//This class is only intended for making simple render commands. For each command one does
		//not make a command do multiple things, only that command.
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};

}
