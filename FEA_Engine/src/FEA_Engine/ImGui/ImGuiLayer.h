#pragma once

#include "FEA_Engine/Layer.h"

#include "FEA_Engine/Events/KeyEvent.h"
#include "FEA_Engine/Events/MouseEvent.h"
#include "FEA_Engine/Events/ApplicationEvent.h"

namespace FEE {

	class FEE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override; 

		//for beginning an ending render of a ImGui window
		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};

}